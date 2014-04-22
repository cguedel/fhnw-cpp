prcpp Übung 2 - JNI

- Der Java-Teil befindet sich im Verzeichnis Java als Eclipse Project
- Der Cpp-Teil befindet sich im Verzeichnis NativeFunctions als Visual Studio 2013 Solution

Für die Ausführung muss in Eclipse der Run-Konfiguration eine Umgebungsvariable PATH hinzugefügt werden:
  PATH=${project_loc}\..\NativeFunctions\x64\Release (oder Debug für Debug-Build)
  
Vor der Ausführung muss die Cpp-Solution kompiliert werden.

Der Output des Test-Programmes ist im File 'MatrixTest.java' ganz unten zu finden.
