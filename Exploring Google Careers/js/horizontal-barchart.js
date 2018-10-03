// References: 
// Horizontal Bar Chart: https://bl.ocks.org/alandunning/7008d0332cc28a826b37b3cf6e7bd998
// Axis Labels: https://bl.ocks.org/d3noob/23e42c8f67210ac6c678db2cd07a747e

function second(csv) {
    // SVG and properties
    var svg = d3.select(".second-svg");
    var margin = {top: 20, right: 120, bottom: 30, left: 180};
    var width = +svg.attr("width") - margin.left - margin.right;
    var height = +svg.attr("height") - margin.top - margin.bottom;

    // Text label for the x axis
    svg.append("text")             
        .attr("transform", "translate(" + (width + margin.left + margin.right/2) + " ," + (height + margin.top + margin.bottom/2) + ")")
        .style("text-anchor", "middle")
        .attr("font-weight", "bold")
        .text("Number of Jobs");

    // Text label for the y axis
    svg.append("text")
        .attr("transform", "translate(" + (margin.left) + " ," + (margin.top - 8) + ")")
        .style("text-anchor", "middle")
        .attr("font-weight", "bold")
        .text("Job Category");

    // Scale for axis
    var x = d3.scaleLinear().range([0, width]);
    var y = d3.scaleBand().range([height, 0]);

    // Barchart
    var barchart = svg.append("g")
            .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    // The span element in h3 tag
    var yearH3 = d3.select(".second-year");

    run(csv);
    
    function run(csv) {
        var data = preprocess(csv);

        // Clear memory
        // csv = undefined;
        
        d3.select(".second-slider")
            .on("input", function() { sliderEvt(data, parseInt(this.value)); });
        
        var subset = subsetByNumOfYears(data, "total");
        renderBarchart(subset);
    }

    function preprocess(csv) {
        // Subset data by job category and for each years of experience get associated job count
        var data = {};
        var numOfRows = csv.length;
        for (var rowIdx = 0; rowIdx < numOfRows; rowIdx++) {
            var row = csv[rowIdx];
            var category = row["Category"];

            // Job category as key
            if (!data.hasOwnProperty(category)) {
                data[category] = {};
                data[category]["total"] = 0; // Job count regardless of years of experience
            }

            // Retrieve years of experience required
            var re = /[0-9]+ year/;
            var match = re.exec(row["Minimum Qualifications"]);
            var numOfYears = (match === null) ? 0 : parseInt(match[0]);
            
            // Years of experience as key
            // Job count as value
            if (data[category].hasOwnProperty(numOfYears)) {
                data[category][numOfYears] += 1;   
            } else {
                data[category][numOfYears] = 1; 
            }
            data[category]["total"] += 1;
        }

        return data;
    }

    function sliderEvt(data, numOfYears) {
        if (numOfYears === 0) {
            yearH3.text("Not Stated");
        } else if (numOfYears === 16) {
            yearH3.text("ALL");
        } else {
            yearH3.text(numOfYears);
        }
        
        if (numOfYears === 16) {
            numOfYears = "total";
        }

        var subset = subsetByNumOfYears(data, numOfYears);
        clearBarchart();
        renderBarchart(subset);
    }

    function subsetByNumOfYears(data, numOfYears) {
        var subset = [];
        for (var category in data) {
            if (data[category].hasOwnProperty(numOfYears)) {
                subset.push({"category": category, "count": data[category][numOfYears]})
            }
        }
        // Sort by count
        subset.sort(function(a, b) {
            return a["count"] - b["count"];
        });
        return subset;
    }

    function clearBarchart() {
        barchart.selectAll("*").remove();
    }

    function renderBarchart(data) {
        // Scale for axis
        x.domain([0, d3.max(data, function(d) { return d.count; })]);
        y.domain(data.map(function(d) { return d.category; }));
        
        // X axis
        barchart.append("g")
            .attr("transform", "translate(0," + height + ")")
            .call(d3.axisBottom(x));

        // Y axis
        barchart.append("g")
            .style("font-size", "0.7em")
            .call(d3.axisLeft(y));

        // Bars
        barchart.selectAll(".second-bar")
            .data(data)
            .enter()
                .append("rect")
                .attr("class", "second-bar")
                .transition()
                .attr("x", 0)
                .attr("height", y.bandwidth() - 4)
                .attr("width", function(d) { return x(d.count); })
                .attr("y", function(d) { return y(d.category); });
        
        // Text
        barchart.selectAll(".second-text")
            .data(data)
            .enter()
                .append("text")
                .transition()
                .text(function(d) { return d.count; })
                .attr("fill", "purple")
                .attr("font-weight", "bold")
                .attr("x", function(d) { return x(d.count) + 5; })
                .attr("y", function(d, i) { return y(d.category) + y.bandwidth()/2 + 3; });
    }
}