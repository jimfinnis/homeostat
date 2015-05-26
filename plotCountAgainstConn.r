data = read.csv("f")
attach(data)

fit = nls(count ~ a*(conn**3) + b*(conn**2) + c*conn + d,start=list(a=1,b=1,c=1,d=1))
new = data.frame(conn=seq(min(conn),max(conn),len=292))

pdf("foo.pdf")
plot(conn,count)
lines(new$conn,predict(fit,newdata=new))
dev.off()

