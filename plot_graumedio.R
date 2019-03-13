library(readr)

graumedio <- read_delim("~/gsop-cpp/graumedio.txt", ";", escape_double = FALSE, col_names = FALSE, trim_ws = TRUE)
graumedio2 <- read_delim("~/gsop-cpp/graumedio2.txt", ";", escape_double = FALSE, col_names = FALSE, trim_ws = TRUE)
graumedio3 <- read_delim("~/gsop-cpp/graumedio3.txt", ";", escape_double = FALSE, col_names = FALSE, trim_ws = TRUE)

graumediom1 <- read_delim("~/gsop-cpp/graumediom1.txt", ";", escape_double = FALSE, col_names = FALSE, trim_ws = TRUE)
graumediom12 <- read_delim("~/gsop-cpp/graumediom12.txt", ";", escape_double = FALSE, col_names = FALSE, trim_ws = TRUE)
graumediom13 <- read_delim("~/gsop-cpp/graumediom13.txt", ";", escape_double = FALSE, col_names = FALSE, trim_ws = TRUE)

library(ggplot2)

table01 <- 0;
  

e01 <- rbind(
  setNames(test <- data.frame(graumedio$X1,graumedio$X2,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio$X1,graumedio$X3,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio$X1,graumedio$X4,"Ephs",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio$X1,graumedio$X5,"avgDegree",stringsAsFactors = FALSE), c("cycle","qtd","type"))
);

e02 <- rbind(
  setNames(test <- data.frame(graumedio2$X1,graumedio2$X2,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio2$X1,graumedio2$X3,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio2$X1,graumedio2$X4,"Ephs",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio2$X1,graumedio2$X5,"avgDegree",stringsAsFactors = FALSE), c("cycle","qtd","type"))
);

e03 <- rbind(
  setNames(test <- data.frame(graumedio3$X1,graumedio3$X2,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio3$X1,graumedio3$X3,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio3$X1,graumedio3$X4,"Ephs",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumedio3$X1,graumedio3$X5,"avgDegree",stringsAsFactors = FALSE), c("cycle","qtd","type"))
);

e04 <- rbind(
  setNames(test <- data.frame(graumediom1$X1,graumediom1$X2,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom1$X1,graumediom1$X3,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom1$X1,graumediom1$X4,"Ephs",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom1$X1,graumediom1$X5,"avgDegree",stringsAsFactors = FALSE), c("cycle","qtd","type"))
);
e05 <- rbind(
  setNames(test <- data.frame(graumediom12$X1,graumediom12$X2,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom12$X1,graumediom12$X3,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom12$X1,graumediom12$X4,"Ephs",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom12$X1,graumediom12$X5,"avgDegree",stringsAsFactors = FALSE), c("cycle","qtd","type"))
);
e06 <- rbind(
  setNames(test <- data.frame(graumediom13$X1,graumediom13$X2,"A",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom13$X1,graumediom13$X3,"B",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom13$X1,graumediom13$X4,"Ephs",stringsAsFactors = FALSE), c("cycle","qtd","type")),
  setNames(test <- data.frame(graumediom13$X1,graumediom13$X5,"avgDegree",stringsAsFactors = FALSE), c("cycle","qtd","type"))
);

ggplot()+geom_line(data=e01, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e02, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e03, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e04, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e05, aes(x=cycle,y=qtd,group=type,colour=type))
ggplot()+geom_line(data=e06, aes(x=cycle,y=qtd,group=type,colour=type))
