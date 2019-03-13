#junto <- rbind(eph00, eph005,eph01,eph015,eph02,eph025,eph03)

library(readr)
eph00 <- read_delim("~/gsop-cpp/exp01/eph00.txt", 
                    ";", escape_double = FALSE, col_names = FALSE, 
                    trim_ws = TRUE)
eph005 <- read_delim("~/gsop-cpp/exp01/eph005.txt", 
                     ";", escape_double = FALSE, col_names = FALSE, 
                     trim_ws = TRUE)
eph01 <- read_delim("~/gsop-cpp/exp01/eph01.txt", 
                    ";", escape_double = FALSE, col_names = FALSE, 
                    trim_ws = TRUE)
eph015 <- read_delim("~/gsop-cpp/exp01/eph015.txt", 
                     ";", escape_double = FALSE, col_names = FALSE, 
                     trim_ws = TRUE)
eph02 <- read_delim("~/gsop-cpp/exp01/eph02.txt", 
                    ";", escape_double = FALSE, col_names = FALSE, 
                    trim_ws = TRUE)
eph025 <- read_delim("~/gsop-cpp/exp01/eph025.txt", 
                     ";", escape_double = FALSE, col_names = FALSE, 
                     trim_ws = TRUE)
eph03 <- read_delim("~/gsop-cpp/exp01/eph03.txt", 
                    ";", escape_double = FALSE, col_names = FALSE, 
                    trim_ws = TRUE)


junto <- {}
juntotmp <- {}
juntotmp <- cbind(eph00[eph00$X1==500,3],"A",0.0)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- {}
juntotmp <- cbind(eph00[eph00$X2==500,3],"B",0.0)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- {}
juntotmp <- cbind(eph00[eph00$X3==-1,3],"Undef.",0.0)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)

juntotmp <- {}
juntotmp <- cbind(eph005[eph005$X1==500,3],"A",0.05)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- cbind(eph005[eph005$X2==500,3],"B",0.05)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- {}
juntotmp <- cbind(eph005[eph005$X3==-1,3],"Undef.",0.05)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)

juntotmp <- {}
juntotmp <- cbind(eph01[eph01$X1==500,3],"A",0.1)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- cbind(eph01[eph01$X2==500,3],"B",0.1)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- {}
juntotmp <- cbind(eph01[eph01$X3==-1,3],"Undef.",0.1)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)

juntotmp <- {}
juntotmp <- cbind(eph015[eph015$X1==500,3],"A",0.15)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- cbind(eph015[eph015$X2==500,3],"B",0.15)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- {}
juntotmp <- cbind(eph015[eph015$X3==-1,3],"Undef.",0.15)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)

juntotmp <- {}
juntotmp <- cbind(eph02[eph02$X1==500,3],"A",0.2)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- cbind(eph02[eph02$X2==500,3],"B",0.2)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- {}
juntotmp <- cbind(eph02[eph02$X3==-1,3],"Undef.",0.2)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)

juntotmp <- {}
juntotmp <- cbind(eph025[eph025$X1==500,3],"A",0.25)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- cbind(eph025[eph025$X2==500,3],"B",0.25)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- {}
juntotmp <- cbind(eph025[eph025$X3==-1,3],"Undef.",0.25)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)


juntotmp <- {}
juntotmp <- cbind(eph03[eph03$X1==500,3],"A",0.3)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- cbind(eph03[eph03$X2==500,3],"B",0.3)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)
juntotmp <- {}
juntotmp <- cbind(eph03[eph03$X3==-1,3],"Undef.",0.3)
colnames(juntotmp) <- c("tfix","tipo","bonus")
junto <- rbind(junto,juntotmp)



#load("junto.RData")
junto$tfix <- as.integer(junto$tfix)
#junto2k <- junto[junto$tfix<2001,]
library(ggplot2)
#ggplot(junto2k, aes(x=bonus,y=tfix,fill=tipo))+geom_boxplot()

junto$bonus <- as.character(junto$bonus)
juntoboxplot <- junto[junto$tfix!=-1,]
ggplot(juntoboxplot, aes(x=bonus,y=tfix,fill=tipo))+geom_boxplot()
library(ggthemes)
library(extrafont)

wins <- data.frame(table(junto[,c(2,3)]))
ggplot()+geom_line(data=wins, aes(x=bonus,y=Freq,group=tipo,colour=tipo), size=2)+scale_x_discrete(breaks=wins$bonus)

wins2 <- data.frame(table(juntoboxplot[,c(2,3)]))
wins2 <- wins2[wins2$tipo!="Undef.",]
ggplot()+geom_line(data=wins2, aes(x=bonus,y=Freq,group=tipo,colour=tipo), size=2)+scale_x_discrete(breaks=wins2$bonus)
