using DataFrames
using CSV
using Plots

function main()

   theme(:ggplot2)
   data = CSV.read("../data/clusters.csv", DataFrame, header=false)

   plot(data[!, 1], data[!, 2], data[!, 3], color=data[!, 4], st=:scatter, label="")
   title!("Data set")

   savefig("../images/clusters.png")
end

main()
