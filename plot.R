if (!require(ggplot2))
  install.packages("ggplot2", repos = "http://cran.us.r-project.org")

res <- read.csv2("res.csv")
p <- ggplot(data = res, aes(x = n, y = useful_slots))
p <- p + geom_point(size = 1)
p <- p + geom_smooth()
print(p)
