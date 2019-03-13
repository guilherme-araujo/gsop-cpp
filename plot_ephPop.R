

library(readr)
h15_epht003 <- read_delim("~/gsop-cpp/exp01/h15-epht003.txt", 
                          ";", escape_double = FALSE, col_names = FALSE, 
                          trim_ws = TRUE)
h15_epht005 <- read_delim("gsop-cpp/exp01/h15-epht005.txt", 
                          ";", escape_double = FALSE, col_names = FALSE, 
                          trim_ws = TRUE)
h15_epht010 <- read_delim("gsop-cpp/exp01/h15-epht010.txt", 
                          ";", escape_double = FALSE, col_names = FALSE, 
                          trim_ws = TRUE)
h15_epht020 <- read_delim("gsop-cpp/exp01/h15-epht020.txt", 
                          ";", escape_double = FALSE, col_names = FALSE, 
                          trim_ws = TRUE)
h15_epht030 <- read_delim("gsop-cpp/exp01/h15-epht030.txt", 
                          ";", escape_double = FALSE, col_names = FALSE, 
                          trim_ws = TRUE)
h15_epht040 <- read_delim("gsop-cpp/exp01/h15-epht040.txt", 
                          ";", escape_double = FALSE, col_names = FALSE, 
                          trim_ws = TRUE)
h15_epht050 <- read_delim("gsop-cpp/exp01/h15-epht050.txt", 
                          ";", escape_double = FALSE, col_names = FALSE, 
                          trim_ws = TRUE)
h15_epht100 <- read_delim("gsop-cpp/exp01/h15-epht100.txt", 
                          ";", escape_double = FALSE, col_names = FALSE, 
                          trim_ws = TRUE)

library(ggplot2)


e003 <- {}
e003 <- rbind(
setNames(data.frame(strtoi(rownames(h15_epht003)),h15_epht003$X1,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
setNames(data.frame(strtoi(rownames(h15_epht003)),h15_epht003$X2,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
setNames(data.frame(strtoi(rownames(h15_epht003)),h15_epht003$X3,"Eph",stringsAsFactors = FALSE), c("cycle","qtd","type")))

e005 <- rbind(
  setNames(data.frame(strtoi(rownames(h15_epht005)),h15_epht005$X1,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht005)),h15_epht005$X2,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht005)),h15_epht005$X3,"Eph",stringsAsFactors = FALSE), c("cycle","qtd","type")))

e010 <- rbind(
  setNames(data.frame(strtoi(rownames(h15_epht010)),h15_epht010$X1,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht010)),h15_epht010$X2,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht010)),h15_epht010$X3,"Eph",stringsAsFactors = FALSE), c("cycle","qtd","type")))

e020 <- rbind(
  setNames(data.frame(strtoi(rownames(h15_epht020)),h15_epht020$X1,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht020)),h15_epht020$X2,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht020)),h15_epht020$X3,"Eph",stringsAsFactors = FALSE), c("cycle","qtd","type")))

e030 <- rbind(
  setNames(data.frame(strtoi(rownames(h15_epht030)),h15_epht030$X1,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht030)),h15_epht030$X2,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht030)),h15_epht030$X3,"Eph",stringsAsFactors = FALSE), c("cycle","qtd","type")))

e040 <- rbind(
  setNames(data.frame(strtoi(rownames(h15_epht040)),h15_epht040$X1,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht040)),h15_epht040$X2,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht040)),h15_epht040$X3,"Eph",stringsAsFactors = FALSE), c("cycle","qtd","type")))

e050 <- rbind(
  setNames(data.frame(strtoi(rownames(h15_epht050)),h15_epht050$X1,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht050)),h15_epht050$X2,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht050)),h15_epht050$X3,"Eph",stringsAsFactors = FALSE), c("cycle","qtd","type")))

e100 <- rbind(
  setNames(data.frame(strtoi(rownames(h15_epht100)),h15_epht100$X1,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht100)),h15_epht100$X2,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(data.frame(strtoi(rownames(h15_epht100)),h15_epht100$X3,"Eph",stringsAsFactors = FALSE), c("cycle","qtd","type")))


ggplot()+geom_line(data=e003, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e005, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e010, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e020, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e030, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e040, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e050, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e100, aes(x=cycle,y=qtd,group=type,colour=type))


