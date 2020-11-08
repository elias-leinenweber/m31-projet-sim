library(ggplot2)

#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

if (length(args)!=2) {
  stop("arg1 : u ou b (uniforme/beb)\narg2 : n ou m (nombre de slots utiles ou moyenne de messages en attente)", call.=FALSE)
} else {
    print(args[1])
    print(args[2])
}

df <- read.table("data", sep="\t", header=TRUE)
head(df)
df$moyenneMessagesEnAttente <-with(df, nbMessagesEnAttente * 1.0 / nbStations)#/ nbStations)

head(df)

y_axis <- ""
if (args[2] == "n") {
    p <- ggplot(data=df, aes(x=nbStations, y=nbSlotsUtiles))
    y_axis <-"Nombre de slots utiles"
} else if(args[2] == "m") {
    p <- ggplot(data=df, aes(x=nbStations, y=moyenneMessagesEnAttente))
    y_axis <- "Moyenne de messages en attente par stations"
}else {
    stop("Deuxième argument non valable.");
}
titre <- "Sans titre"
if (args[1] == "u") {
    titre <- "Aloha avec relance uniforme"
} else if (args[1] == "b") {
    titre <- "Aloha avec relance beb"
}

if (args[1] == "u")
p <- p + geom_point(size=0, alpha=0.1)
p <- p + geom_smooth()
p <- p + labs(  x="Nombre de stations",
                y=y_axis,
                title=titre)

print(p)


