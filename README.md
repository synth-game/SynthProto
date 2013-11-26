This is the prototype of the Synth project, a student platformer puzzle game, in where playing with light is the key.

To start working on this prototype, follow this different steps :

  - Get a cocosd2-x 3.0 alpha folder, with our custom code
  - Go to tools/project_creator/ folder with a shell
  - Do : py create_project.py -p SynthProto -k imac3.synth.proto -l cpp
  - Go to the new projects/SynthProto/ folder (from the root repertory)
  - It's time to get the remote code and to plug with Github :
    - Delete the Classes and Resources folder in your project repertory
    - then do:
      - git init
      - git remote set-url origin https://github.com/synth-game/SynthProto.git
      - git pull origin master

You can now start working !
