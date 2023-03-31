#         _          _ ______ _____ _____ 
#        (_)        | |  ____|  __ \_   _|
#   _ __  ___  _____| | |__  | |  | || |  
#  | '_ \| \ \/ / _ \ |  __| | |  | || |  
#  | |_) | |>  <  __/ | |____| |__| || |_ 
#  | .__/|_/_/\_\___|_|______|_____/_____|
#  | |                                    
#  |_|                                    
                             
# www.pixeledi.eu | twitter.com/pixeledi
# Whisper Speech Recognition | V 1.0 | 09.2022
# Transcribe a whole Folder and save the transcription as a *.txt File
# Source: https://github.com/openai/whisper

import whisper
from pathlib import Path

# path with slash not backslash!
filepath = 'myfolder'
for p in Path(filepath).glob('*.mp4'):
    with p.open() as f:
        print(f"{p.name}:\n")

        model = whisper.load_model("base")
        filename= filepath+"/"+p.name
        result = model.transcribe(filename)

        txtFilename = filename[0:-4]+".txt"
        with open(txtFilename, 'w') as f:
            f.write(str(result['text']))
            f.close()