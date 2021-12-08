meta:
  id: mapdata_dat
  endian: le
  bit-endian: le
  
seq:
  - id: mission_dir
    type: u4
    repeat: eos
    doc: |
      Path where the game will look for the original campaigns map file ("staredit/scenario.chk") and the WAV files ("staredit/wav/").
