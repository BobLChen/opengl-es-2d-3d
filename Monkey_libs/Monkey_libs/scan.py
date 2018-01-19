import os
import sys

sourcedir = os.getcwd()

for parentDir, dirName, fileNames in os.walk(sourcedir):
    for fileName in fileNames:
        if fileName.endswith('cpp') or fileName.endswith('c'):
            filePath = os.path.join(parentDir, fileName)
            idx = filePath.rfind("src")
            filePath = filePath[idx:]
            print filePath + " \\"
            pass
        pass
    pass