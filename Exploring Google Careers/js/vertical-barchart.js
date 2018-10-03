// Reference: https://bl.ocks.org/mbostock/3885304

function first(csv) {
    // SVG and properties
    var svg = d3.select(".first-svg"),
        margin = {top: 40, right: 20, bottom: 40, left: 60},
        width = +svg.attr("width") - margin.left - margin.right,
        height = +svg.attr("height") - margin.top - margin.bottom;

    // Text label for the x axis
    svg.append("text")             
        .attr("transform", "translate(" + (width + margin.left + margin.right)/2 + " ," + (height + margin.top + margin.bottom - 4) + ")")
        .style("text-anchor", "middle")
        .attr("font-weight", "bold")
        .text("Programming Language");

    // Text label for the y axis
    svg.append("text")
        .attr("transform", "translate(" + (margin.left) + " ," + (margin.top - 24) + ")")
        .style("text-anchor", "middle")
        .attr("font-weight", "bold")
        .text("Number of Jobs");

    // Scaling
    var x = d3.scaleBand().rangeRound([0, width]).padding(0.1),
        y = d3.scaleLinear().rangeRound([height, 0]);

    // Barchart
    var barchart = svg.append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    run(csv);

    function run(csv) {
        var data = preprocess(csv);
        // csv = undefined; // Clear memory

        var subset = subsetByLanguage(data);
        renderBarchart(subset);
    };

    function preprocess(csv) {
        var data = "";
        var numOfRows = csv.length;
        for (var rowIdx = 0; rowIdx < numOfRows; rowIdx++) {
            data += csv[rowIdx]["Minimum Qualifications"].toLowerCase();
        }
        return data;
    }

    function subsetByLanguage(data) {
        var subset = [];

        var LANGUAGES = ["python", "java", "c++", "php", "javascript", "objective-c", "ruby", "perl", "c", "c#", "sql", "kotlin", "go", "r", "matlab", "bash", "assembly"];
        var numOfLanguages = LANGUAGES.length;
        for (var languageIdx = 0; languageIdx < numOfLanguages; languageIdx++) {
            subset[languageIdx] = {"language": LANGUAGES[languageIdx], "count": 0};
        }

        // Split the huge string into words and punctuations
        var re = /[\w'+#-]+|[.!?;’]/g;
        var matches = data.match(re);
        
        // Increment count for every language
        var matchLen = matches.length;
        for (var matchIdx = 0; matchIdx < matchLen; matchIdx++) {
            var match = matches[matchIdx];
            var languageIdx = LANGUAGES.indexOf(match);
            if (languageIdx != -1) {
                subset[languageIdx]["count"]++;
            }
        }

        // Sort by count
        subset.sort(function(a, b) {
            return b.count - a.count;
        });

        // Capitalize
        var subsetLen = subset.length;
        for (var subsetIdx = 0; subsetIdx < subsetLen; subsetIdx++) {
            subset[subsetIdx]["language"] = subset[subsetIdx]["language"][0].toUpperCase() + subset[subsetIdx]["language"].slice(1);
        }
        return subset;
    }

    function renderBarchart(data) {
        // Scaling
        x.domain(data.map(function(d) { return d.language; }));
        y.domain([0, d3.max(data, function(d) { return d.count; })]);

        // X-axis
        barchart.append("g")
            .attr("transform", "translate(0," + height + ")")
            .style("font-size", "0.7em")
            .call(d3.axisBottom(x));

        // Y-axis
        barchart.append("g")
            .call(d3.axisLeft(y));

        // Bars
        barchart.selectAll(".first-bar")
            .data(data)
            .enter()
                .append("rect")
                .attr("class", "first-bar")
                .attr("x", function(d) { return x(d.language); })
                .attr("y", function(d) { return y(d.count); })
                .attr("width", x.bandwidth())
                .attr("height", function(d) { return height - y(d.count); });

        // Text
        barchart.selectAll(".first-text")
            .data(data)
            .enter()
                .append("text")
                .transition()
                .text(function(d) { return d.count; })
                .attr("fill", "purple")
                .attr("font-weight", "bold")
                .attr("x", function(d) { return x(d.language) + x.bandwidth()/3; })
                .attr("y", function(d, i) { return y(d.count) - 2; });
    }
}