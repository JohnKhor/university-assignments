// Constant
var STATES = ["PERLIS", "KEDAH", "PULAU PINANG", "PERAK", "SELANGOR", "KUALA LUMPUR", "NEGERI SEMBILAN", "MELAKA", "JOHOR", "PAHANG", "KELANTAN", "TERENGGANU", "SABAH", "SARAWAK"];

// Headline
d3.select("body")
    .append("h1")
    .text("Road Accidents and Injuries in Malaysia");

// Huge container containing interaction, message and legend
var hugeContainter = d3.select("body")
    .append("div")
    .style("display", "flex");

// Interaction
var interaction = hugeContainter.append("div");

interaction.append("h2")
    .text("Controls: ");
// End interaction

// Slider
var sliderContainer = interaction.append("div");

sliderContainer.append("h3")
    .text("1. Year");

sliderContainer.append("input")
    .attr("type", "range")
    .attr("min", 2011)
    .attr("max", 2015)
    .attr("value", 2011)
    .attr("id", "year");
// End slider

// Dropdown
var dropdownContainer = interaction.append("div");

dropdownContainer.append("h3")
    .text("2. Type");

dropdownContainer.append("select")
    .attr("id", "type");
// End dropdown

// Message
var messageContainer = hugeContainter.append("div")
    .style("padding-left", "100px");

messageContainer.append("h2")
    .text("You are currently viewing: ");

var messageYearStr = "Year: ",
    messageTypeStr = "Type: ",
    messageStateStr = "State: ",
    messageCaseStr = "Number of Cases: ";

messageContainer.append("p")
    .text(messageYearStr)
    .attr("id", "message-year");

messageContainer.append("p")
    .text(messageTypeStr)
    .attr("id", "message-type");

messageContainer.append("p")
    .text(messageStateStr + "None")
    .attr("id", "message-state");

messageContainer.append("p")
    .text(messageCaseStr + 0)
    .attr("id", "message-case");
// End message

// Legend
var legendContainer = hugeContainter.append("div")
    .style("padding-left", "100px");

legendContainer.append("h2")
    .text("Legend: ");

var legendCanvas = legendContainer.append("svg")
    .attr("width", 250)
    .attr("height", 180);

legendCanvas.append("g")
    .attr("class", "legend");
// End legend

// Canvas
var width = 1000;
var height = 380;

var mainCanvas = d3.select("body")
    .append("svg")
    .attr("width", width)
    .attr("height", height);
// End canvas

// Map projection
var projection = d3.geoMercator()
    .scale(1)
    .translate([0,0]);

// Path generator
var path = d3.geoPath()
    .projection(projection);

// Load in Malaysia Accident and Injury data
d3.csv("data.csv", function(csv) {
    // Convert string to number
    csv.forEach(function(row) {
        for (var col in row) {
            if (!isNaN(row[col])) {
                row[col] = parseInt(row[col]);
            }
        }
    });

    // Construct statistics object
    var statistics = {};
    for (var i = 0; i < STATES.length; i++) {
        // Subset data by state
        statistics[STATES[i]] = csv.filter(function(row) {
            return row["NEGERI"] === STATES[i];
        });
        // Remove redundant state column
        statistics[STATES[i]].forEach(function(row) {
            delete row["NEGERI"];
        });
    }
    
    // Dropdown
    var types = csv["columns"].filter(function(name) {
        return name !== "NEGERI" && name !== "TAHUN";
    });

    d3.select("#type")
        .selectAll("option")
        .data(types)
        .enter()
            .append("option")
            .attr("value", function(d) { return d; })
            .append("text")
            .text(function(d) { return d; });
    // End dropdown
    
    // Load in Malaysia GeoJSON data
    d3.json("malaysia_geo.json", function(json) {
        // Define scaling and translation based on bounding box
        var bounds = path.bounds(json);
        var s = 0.95 / Math.max((bounds[1][0] - bounds[0][0]) / width, (bounds[1][1] - bounds[0][1]) / height);
        var t = [(width - s * (bounds[1][0] + bounds[0][0])) / 2, (height - s * (bounds[1][1] + bounds[0][1])) / 2];

        // Update scaling and translation
        projection
            .scale(s)
            .translate(t);

        // Bind data and create one path per GeoJSON feature
        mainCanvas.append("g")
            .attr("class", "tracts")
            .selectAll("path")
            .data(json.features)
            .enter()
                .append("path")
                .attr("d", path)
                .attr("fill-opacity", 0.8)
                .attr("stroke", "#222")
                .on("mouseover", function(d) { mapMouseOver(d); })
                .on("mouseout", mapMouseOut);

        // Initialize with initial year and type
        updateOnChange(json, statistics);

        // Event handlers for slider and dropdown
        d3.select("#year").on("input", function() { updateOnChange(json, statistics) });
        d3.select("#type").on("change", function() { updateOnChange(json, statistics) });
    }); // End loading json
}); // End loading csv

function mapMouseOver(jsonData) {
    var jsonState = jsonData.properties.NAME_1.toUpperCase();
    if (STATES.indexOf(jsonState) != -1) {
        d3.select("#message-state").text(messageStateStr + jsonState);
        d3.select("#message-case").text(messageCaseStr + jsonData.properties.value);   
    }
}

function mapMouseOut() {
    d3.select("#message-state").text(messageStateStr + "None");
    d3.select("#message-case").text(messageCaseStr + 0);
}

function subsetStatByYearAndType(statistics, year, type) {
    var subsetStat = [];

    // Subset statistics by state
    for (var state in statistics) {
        // Retrive value for given year and type
        var value = statistics[state].filter(function(row) {
            return row["TAHUN"] === parseInt(year);
        })[0][type];
        // Insert into array
        subsetStat[state] = value;
    }

    return subsetStat;
}

function defineColorScale(values) {
    return d3.scaleLinear()
        .domain([d3.min(values), d3.max(values)])
        .range([d3.rgb("#fff"), d3.rgb("#f00")]);
}

function binning(values, numberOfBins) {
    var minimum = d3.min(values);
    var maximum = d3.max(values);
    var step = (maximum - minimum) / (numberOfBins - 1);

    var bins = [minimum];
    var binValue = minimum;
    for (var i = 0; i < numberOfBins - 2; i++) {
        binValue = Math.round(binValue + step);
        bins.push(binValue);
    }
    bins.push(maximum);
    
    return bins;
}

function legendMouseOver(binValue, binIdx, prevBinValue, colorScale) {
    // Cancels ongoing transition for quick mouseovers
    d3.select(".tracts")
        .selectAll("path")
        .interrupt();
    
    // Range
    var begin = (binIdx === 0) ? 0 : prevBinValue + 1;
    var end = binValue;
    
    // Fade other colors if not within range
    d3.select(".tracts")
        .selectAll("path")
        .attr("fill", function(json) {
            var jsonValue = json.properties.value;
            return (jsonValue >= begin && jsonValue <= end) ? colorScale(binValue) : "#d4d4d4";
        });
}

function renderLegend(colorScale, values) {
    var numberOfBins = 6;
    var bins = binning(values, 6);

    var legendCanvasHeight = +legendCanvas.attr("height");

    var legend = legendCanvas.select(".legend");

    // Hacky way to remove previous rect and text
    legend.selectAll("rect").remove();
    legend.selectAll("text").remove();

    // Square color
    legend.selectAll("rect")    
        .data(bins)
        .enter()
            .append("rect")
            .attr("width", "20")
            .attr("height", "20")
            .attr("x", 0)
            .style("stroke", "black")
            .attr("y", function(d, i) { return (legendCanvasHeight - 50) - 25 * i; })
            .attr("fill", function(d) { return colorScale(d); })
            .on("mouseover", function(d, i) { legendMouseOver(d, i, bins[i - 1], colorScale) })
            .on("mouseout", function() { renderPath(colorScale, 50); });

    // Text beside square
    var startVal = 0;
    legend.selectAll("text")
        .data(bins)
        .enter()
            .append("text")
            .text(function(d) { 
                var legendTxt = startVal + " - " + d;
                startVal = d + 1;
                return legendTxt; 
            })
            .attr("y", function(d, i) { return (legendCanvasHeight - 32) - 25 * i; })
            .attr("x", 28)
            .attr("fill", "black");
}

function modifyJson(json, subsetStat) {
    for (var state in subsetStat) {
        // Find the corresponding state inside the GeoJSON
        for (var j = 0; j < json.features.length; j++) {
            var jsonState = json.features[j].properties.NAME_1.toUpperCase();
            if (state === jsonState) {
                // Copy the data value into the JSON
                json.features[j].properties.value = subsetStat[state];
                // Stop looking through the JSON
                break;
            }
        }
    }
}

function renderPath(colorScale, delayTime) {
    mainCanvas.selectAll("path")
        .transition()
        .delay(delayTime)
        .attr("fill", function(d) {
            var jsonState = d.properties.NAME_1.toUpperCase();
            if (STATES.indexOf(jsonState) != -1) {           
                return colorScale(d.properties.value);    
            }
        });
}

function updateOnChange(json, statistics) {
    // Get year
    var range = document.querySelector("#year");
    var year = range.value;

    // Get type
    var select = document.querySelector("select");
    var type = select.options[select.selectedIndex].value;

    // Subset statistics by year and type
    var subsetStat = subsetStatByYearAndType(statistics, year, type);
    
    // Values only
    var values = d3.values(subsetStat);
    
    // Values into six bins
    var valueBins = binning(values, 6);
    
    // Create color scale from values
    var colorScale = defineColorScale(values);
    
    // Update message
    d3.select("#message-year").text(messageYearStr + year);
    d3.select("#message-type").text(messageTypeStr + type);
    
    // Update legend
    renderLegend(colorScale, values);

    // Update map
    modifyJson(json, subsetStat);
    renderPath(colorScale, 0);
}