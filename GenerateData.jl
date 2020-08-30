# Generate random clusters from Gaussian Mixture Distribution
using Distributions
using CSV
using DataFrames
using Random

function generateData(n::Int64)
   # Mean
	µ1 = [ 0.0, 0.0, 0.0 ]
   µ2 = [ 30.0, 30.0, 0.0 ]
   µ3 = [ 0.0, 30.0, 30.0 ]
   # Covariance
   ∑1 = [ 7.0, 8.0, 14.0 ]
   ∑2 = [ 6.0, 5.0, 12.0 ]
   ∑3 = [ 9.0, 13.0, 8.0 ]

   # Multivariate normal distributions
   dist1 = MvNormal(µ1, ∑1)
   dist2 = MvNormal(µ2, ∑2)
   dist3 = MvNormal(µ3, ∑3)

   m = n÷3 + n % 3
   data = hcat(rand(dist1, m), rand(dist2, m), rand(dist3, m))
   df = DataFrame(x1 = data[1, :], x2 = data[2, :], x3 = data[3, :])
   df = df[shuffle(1:end), :]
   return df[1:n, :]
end


function main()
   N = 1000000
   df = generateData(N)
   for (i, k) in enumerate(10.0.^ range(1, stop = 6, length = 11))
      n = trunc(Int64, k)
      filename = "data/$i.csv"
      CSV.write(filename, df[1:n, :])
   end
end


main()
