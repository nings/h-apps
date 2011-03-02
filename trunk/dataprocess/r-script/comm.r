library(igraph)
g <- read.graph("~/svn/h-apps/dataprocess/r-script/wsconn.net", format="pajek")

wt <- walktrap.community(g, modularity=TRUE)
dend <- as.dendrogram(wt, use.modularity=TRUE)
plot(dend, nodePar=list(pch=c(NA, 20)))