SELECT NAME FROM SONGS WHERE ARTIST_ID = (SELECT id FROM ARTISTS WHERE NAME = "Post Malone");