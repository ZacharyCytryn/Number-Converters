all:
	javac FloatDecompose.java

test:
	javac -cp ./lib/junit-platform-console-standalone-1.9.1.jar:. *.java
	java -jar ./lib/junit-platform-console-standalone-1.9.1.jar --disable-banner --disable-ansi-colors -cp . -c FloatDecomposeTests

clean:
	rm *.class

.PHONY: all clean test