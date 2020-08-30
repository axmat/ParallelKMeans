using DataFrames
using CSV
using Plots


function main()
   data = CSV.read("data/clusters.csv", header=false)
   theme(:ggplot2)
	plot(data[!, 1], data[!, 2], data[!, 3], color=data[!, 4]; st=:scatter3d,
       title="scatter plot",
       label="")
   savefig("images/scatter_plot.png")
end


main()
