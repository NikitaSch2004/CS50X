SELECT AVG(ENERGY) FROM SONGS WHERE ARTIST_ID =(SELECT ID FROM ARTISTS WHERE NAME = "Drake");