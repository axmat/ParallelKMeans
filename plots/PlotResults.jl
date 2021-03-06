using DataFrames
using CSV
using Plots

function main()

   theme(:ggplot2)
   data = CSV.read("../data/benchmark.csv", DataFrame, header = false)

   plot(log10.(data[!, 1]), color=:blue,
        title="Average run time",
        label="Sequantial",
        xaxis=collect(1:12),
        xlabel="Dataset size (log-10 scale)",
        ylabel="Average Time (log-10 scale)")
   plot!(log10.(data[!, 2]), color=:red, label="Parallel")
   savefig("../images/btime.png")

   plot(data[!, 1], color=:blue,
        title="Average run time",
        label="Sequantial",
        xaxis=collect(1:12),
        xlabel="Dataset size (log-10 scale)",
        ylabel="Average Time (s)")
        plot!(data[!, 2], color=:red, label="Parallel")
   savefig("../images/btime_nolog.png")

   speedup = data[!, 1] ./ data[!, 2]
   plot(speedup, color=:green,
        title="",
        label="",
        xlabel="Dataset size (log-10 scale)",
        ylabel="Speedup")
   savefig("../images/speedup.png")
end


main()
