function fourth(data) {
    var mapWidth = 1024, mapHeight = 1024;
    
    var c10 = d3.scaleOrdinal(d3.schemeCategory10);

    var projection = d3.geoMercator();

    var path = d3.geoPath()
        .projection(projection);
    
    var color = d3.scaleLog()
            .domain([1, 600]) // log domain can't contain 0! silly bug.
            .range(["#DDD1E7", "#7647A2"]);
            
    var svg_legend = d3.select(".four-wrapper").append("svg")
        .attr("width", mapWidth)
        .attr("height", 80)
        .attr("id", "four_svg_legend");
        
    var svg = d3.select(".four-wrapper").append("svg")
        .attr("width", mapWidth)
        .attr("height", mapHeight)
        .attr("id", "four_svg");
        
    svg = d3.select("#four_svg")
        .call(d3.zoom().scaleExtent([1, 50]).on("zoom", function () {
              svg.attr("transform", d3.event.transform)
         }))
        .append("g");
        
    var legends = [];
    var ticks = [];
    for (var i = 1; i <= 601; i+= 40) {
        legends.push([i, color(i)]);
        ticks.push(i);
    }
    
    /* LEGEND FOR MAP CHOROPLETH */
    /******************************************************************************************/
    
    var x = d3.scaleLinear()
        .domain([1, 601])
        .rangeRound([0.5 *mapWidth, 0.9*mapWidth]);
        
    var g = svg_legend.append("g")
    .attr("class", "four-key")
    .attr("transform", "translate(0,40)");

    var width = x(legends[1][0]) - x(legends[0][0]);
    g.selectAll("rect")
      .data(legends)
      .enter().append("rect")
        .attr("height", 8)
        .attr("x", function(d) { return x(d[0]); })
        .attr("y", 0)
        .attr("width", function(d) { return width; })
        .attr("fill", function(d) { return d[1]; });

    g.append("text")
        .attr("class", "four-caption")
        .attr("x", x.range()[0])
        .attr("y", -6)
        .attr("fill", "#000")
        .attr("text-anchor", "start")
        .attr("font-weight", "bold")
        .text("Number of Jobs");

    g.call(d3.axisBottom(x)
        .tickSize(legends.length)
        .tickFormat(function(x, i) { return x; })
        .tickValues(ticks))
      .select(".domain")
        .remove();

    /******************************************************************************************/

    var mapLabel = svg.append("text")
        .attr("y", 20)
        .attr("x", 0)
        .attr("class", "four-map_neighbourhood_name")
        
            
    var tip = d3.tip()
        .attr('class', 'd3-tip')
        .offset([-10, 0])
        .html(function(d) {
          return "<strong>Country: </strong><span class='details'>" + d.country + "<br></span>" + "<strong>Number of Jobs: </strong><span class='details'>" + d.num_employees +"</span>";
        })
    svg.call(tip);

    queue()
        .defer(d3.json, "./world.topo.json")
        .await(ready); 

    // load TopoJSON file
    function ready(error, world) {
      if (error) throw error;
      neighbourhoods = topojson.feature(world, world.objects.countries); 
      var country_mapping = {"Taiwan, Province of China":"Taiwan", 
                            "United Arab Emirates":"Dubai - United Arab Emirates", 
                            "Korea, Democratic People's Republic of":"South Korea", 
                            "Russian Federation":"Russia", 
                            "Czech Republic":"Czechia"};
      var countries = {};
      var country_employee = [];
      data.forEach(function(d) {
          var location_data = d.Location.split(",");
          var country = trim(location_data[location_data.length-1]);
          if (country == "USA") country = "United States";
          
          if (countries[country] == undefined) {
              countries[country] = 1;
          } else {
            countries[country] += 1;
          }
      });
      
      for (country in countries) {
          country_employee.push({"country":country, "num_employees":countries[country]});
      }
      //prettyPrint2(countries);
      //prettyPrint(countries);
      
      // set default projection values 
      projection
          .scale(1)
          .translate([0, 0]);

      // creates bounding box and helps with projection and scaling
      var b = path.bounds(neighbourhoods),
          s = .95 / Math.max((b[1][0] - b[0][0]) / mapWidth, (b[1][1] - b[0][1]) / mapHeight),
          t = [(mapWidth - s * (b[1][0] + b[0][0])) / 2, (mapHeight - s * (b[1][1] + b[0][1])) / 2];

      // set project with bounding box data
      projection
          .scale(s)
          .translate(t);
      
      // get individual neighbourhoods
      var topo_countries = {};
      svg.selectAll("path")
            .data(neighbourhoods.features)
            .enter().append("path")
            .attr("class", "four-map_neighbourhood")
            .attr("d", path)
            .on("mouseover", mouseover) 
            .on("mouseout", mouseout)
            .attr("class", function(d) {
                var country = d.properties.name;
                if (country in country_mapping) country = country_mapping[country]; // important normalization step, courtesy of manual labour and wrist problems.
                d.num_employees = 0;
                if (countries[country] != undefined) d.num_employees = countries[country];
                d.country = country;
                return "four-map_neighbourhood";
            })
            .attr("fill", function(d) {
                var country = d.properties.name, num_employees = 0;
                if (country in country_mapping) country = country_mapping[country];
                if (countries[country] != undefined) num_employees = countries[country];
                if (num_employees == 0) return "#efefef"; // remember log doesn't have 0 in it's domain.
                return color(num_employees);
            });
            
            
      
      // add the mesh/path between neighbourhoods
      svg.append("path")
            .datum(topojson.mesh(world, world.objects.countries_geo, function(a, b) { return a !== b; }))
            .attr("class", "four-map_mesh")
            .attr("d", path);
            
    }

    function mouseover(d) {
        tip.show(d);
        //console.log(d.country + " has " + d.num_employees + " employees.");
    }

    function mouseout(d) {
        tip.hide(d);
    }
    
    // Utilities
    function trim(str) {
        var i = 0;
        var j = str.length-1;
        while (str[i] == ' ') i += 1;
        while (str[j] == ' ') j -= 1;
        return str.substring(i, j+1);
    }
    
}
