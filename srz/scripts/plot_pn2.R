library(ggplot2)

#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

df <- read.table("data", sep="\t", header=TRUE)
head(df)
df$moyenneMessagesEnAttente <-with(df, nbMessagesEnAttente * 1.0 / nbStations)#/ nbStations)

df$pn <- with(df, proba * nbStations)

head(df)

tail(df)

y_axis <- "Nombre moyen de messages en attente"

titre <- "Aloha avec relance beb, proba = 0.001"#, k=10"


p <- ggplot(data=df,
    aes(x=nbSlots, y=moyenneMessagesEnAttente, colour=factor(pn)))
    
#p <- p + geom_point(size=0, alpha=0.1)
p <- p + geom_smooth()
p <- p + labs(  x="Slot",
                y=y_axis,
                color="p*n",
                title=titre)

png("myplot.png")
print(p)
dev.off()

print(p)


