function third(data) {
    var margin = {top: 30, right: 50, bottom: 30, left: 50};
    var width = 1024 - margin.left - margin.right;
    var height = 500 - margin.top - margin.bottom;    
    
    var svg = d3.select(".three-wrapper").append("svg")
        .attr("width", width)
        .attr("height", height)
        .attr("id", "three_svg");
    
   var tip = d3.tip()
        .attr('class', 'd3-tip')
        .offset([-10, 0])
        .html(function(d) {
          return "<strong>Keyword: </strong><span class='details'>" + d[0] + "<br></span>" + "<strong>Occurences: </strong><span class='details'>" + d[1] +"</span>";
        })
    svg.call(tip);
    
    // compute frequency of words
    var words = {}
    var filter = {"and":1, "to":1, "in":1, "with":1, "of":1, "a":1, "the":1, "or":1, "as":1, "for":1, "an":1, "on":1, "and/or":1, "year":1, "years":1};
    data.forEach(function(d) {
        var prefqual = d["Preferred Qualifications"];
        var tokens = prefqual.split(" "); // simple tokenizing based on ' ' (spaces).
        for (var i = 0; i < tokens.length; i++) {
            var tok = removeSymbol(tokens[i].toLowerCase());
            if (!(tok in filter)) {
                if (words[tok] == undefined) {
                    words[tok] = 1;
                } else {
                    words[tok] += 1;
                }    
            }
        }
    });
    
    var wordfreq = [];
    var threshold = 5; // removes words that occur < 5 times, also less items to sort.
    for (word in words) {
        if (words[word] >= 5) wordfreq.push([word, words[word]]);
    }
    wordfreq.sort(function(a, b) {return b[1]-a[1]});
    wordfreq = wordfreq.slice(0, 30);

    var color = d3.scaleOrdinal(d3.schemeCategory20);
    var fontSize = d3.scalePow().exponent(5).domain([0,1]).range([40,80]);
    
    var layout = d3.layout.cloud()
      .size([width, height])
      .timeInterval(20)
      .words(wordfreq)
      .rotate(function(d) { return 0; })
      .fontSize(function(d,i) { return parseInt(d[1]/20); })
      //.fontStyle(function(d,i) { return fontSyle(Math.random()); })
      .fontWeight(["bold"])
      .text(function(d) { return d[0]; })
      .spiral("rectangular") // "archimedean" or "rectangular"
      .on("end", draw)
      .start();
      
    var g = svg.append("g")
       .attr("transform", "translate(" + margin.left + "," + margin.top + ")");
        
    var wordcloud = g.append("g")
      .attr('class','wordcloud')
      .attr("transform", "translate(" + width/2 + "," + height/2 + ")");
      
    g.append("g")
      .attr("class", "axis")
      .attr("transform", "translate(0," + height + ")")
      .selectAll('text')
      .style('font-size','20px')
      .style('fill',function(d) { return color(d); })
      .style('font','sans serif');
    
    function draw(words) {
        wordcloud.selectAll("text")
            .data(words)
            .enter().append("text")
            .attr('class','word')
            .style("fill", function(d, i) { return color(i); })
            .style("font-size", function(d) { return d.size + "px"; })
            .style("font-family", "Roboto")
            .attr("text-anchor", "middle")
            .attr("transform", function(d) { return "translate(" + [d.x, d.y] + ")rotate(" + d.rotate + ")"; })
            .text(function(d) { return d.text; })
            .on("mouseover", mouseover)
            .on("mouseout", mouseout);
    }
  
  
   function removeSymbol(text) {
       var symbols = {' ':0, '.':1, ',':2, '\'':3, '/':4, ';':5};
       var i = 0, j = text.length-1;
       if (text[i] in symbols) i += 1;
       if (text[j] in symbols) j -= 1;
       return text.substring(i, j+1);
   }
   
   function mouseover(d) {
       tip.show(d);
   }
   
   function mouseout(d) {
       tip.hide(d);
   }
}