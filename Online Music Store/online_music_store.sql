--	+-------------------------------+
--	|				                |
--	|	TIS1101 Assignment	        |	
--	|				                |
--	|	Online Music Store	        |
--	|				                |
--	+-------------------------------+

--	/--------------------/
--	/ I. CREATE DATABASE /
--	/--------------------/

CREATE DATABASE msicstor;
CONNECT TO msicstor;

--	/-------------------/
--	/ II. CREATE TABLES /
--	/-------------------/

CREATE TABLE user
(
 	user_id 	INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1),
 	user_name 	VARCHAR(20),
 	user_email 	VARCHAR(30)
);

CREATE TABLE album
(
	album_id 	INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1),
	album_name 	VARCHAR(30),
	album_artist	VARCHAR(30),
	album_price 	DECIMAL(5,2) WITH DEFAULT 0,
	album_rating 	DECIMAL(2,1) WITH DEFAULT 0.0,
	album_category 	VARCHAR(20),
	album_date	DATE,
	CHECK (album_rating BETWEEN 0.0 AND 5.0),
	CHECK (album_category IN ('New', 'Trending'))
);

CREATE TABLE song
(
	song_id		INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1),
	song_name	VARCHAR(30),
	song_duration	CHAR(5),
	song_price	DECIMAL(4,2),
	song_rating	DECIMAL(2,1) WITH DEFAULT 0.0,
	song_genre	VARCHAR(10),
	album_id	INT,
	FOREIGN KEY (album_id) REFERENCES album,
	CHECK (song_rating BETWEEN 0.0 AND 5.0),
	CHECK (song_genre IN ('Pop', 'Rock', 'Classical', 'Electric', 'Hip-Hop', 'Jazz', 'Karaoke', 'RnB'))
);

CREATE TABLE format
(
	format_id	INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1),
	format_of_song	CHAR(3),
	format_price	DECIMAL(5,2),
	CHECK (format_of_song IN ('mp3', 'wma', 'wav'))
);

CREATE TABLE review
(
	review_id	INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1),
	user_id		INT,
	album_id	INT,
	song_id		INT,
	review_rating	DECIMAL(2,1),
	review_comment	VARCHAR(50),
	FOREIGN KEY (user_id) REFERENCES user,
	FOREIGN KEY (album_id) REFERENCES album,
	FOREIGN KEY (song_id) REFERENCES song,
	CHECK (review_rating BETWEEN 1.0 AND 5.0)
);

CREATE TABLE order
(
	order_id		INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1),
	order_date		DATE,
	order_quantity		INT,
	order_payment_method	VARCHAR(20),
	order_card_num		CHAR(16),	
	order_tax		DECIMAL(3,2),
	order_invoice		DECIMAL(7,2),
	user_id			INT,
	FOREIGN KEY (user_id) REFERENCES user,
	CHECK (order_payment_method IN ('Visa', 'Master', 'Paypal', 'Maybank2u', 'CIMB Clicks'))
);

CREATE TABLE order_detail
(
	order_id	INT NOT NULL,
	album_id	INT NOT NULL,
	format_id	INT NOT NULL,
	order_price	DECIMAL(5,2),
	FOREIGN KEY (order_id) REFERENCES order,
	FOREIGN KEY (album_id) REFERENCES album,
	FOREIGN KEY (format_id) REFERENCES format,
	PRIMARY KEY (order_id, album_id, format_id)
);

--	/-----------------------/
--	/ III. INSERT MOCK DATA /
--	/-----------------------/

INSERT INTO user
	(user_name, user_email)
VALUES
	('John', 'john@gmail.com'),
	('Constantine', 'constantine@hotmail.com'),
	('Taylor', 'taylor@yahoomail.com'),
	('Lucy', 'lucy@gmail.com'),
	('Mary', 'mary@hotmail.com'),
	('Brian', 'brian@yahoomail.com'),
	('Ming', 'ming@gmail.com'),
	('Ali', 'ali@hotmail.com'),
	('Saitama', 'saitama@yahoomail.com');

INSERT INTO album
	(album_name, album_artist, album_category, album_date)
VALUES
	('25', 'Adele', 'New', '2015-11-20'),
	('Purpose', 'Justin Bieber', 'New', '2015-11-13'),
	('The Piano Guys', 'The Piano Guys', 'Trending', '2012-10-02'),
	('The Marshall Mathers LP 2', 'Eminem', NULL, '2013-11-05'),
	('Nothing But the Best', 'Frank Sinatra', 'Trending', '2008-05-13'),
	('Thriller', 'Michael Jackson', 'Trending', '1983-07-29'),
	('Confident', 'Justin Bieber', NULL, '2013-09-08'),
	('Blackstar', 'David Bowie', 'New', '2016-01-08'),
	('Girl On Fire', 'Alicia Keys', NULL, '2012-11-23'),
	('Under The Mistletoe', 'Justin Bieber', 'Trending', '2011-04-18'),
	('Love, Marriage & Divorce', 'Toni Braxton & Babyface', NULL, '2014-01-01'),
	('Night Visions', 'Imagine Dragons', 'Trending', '2012-01-01'),
	('Does This Look Infected?', 'Sum 41', 'Trending', '2002-01-01'),
	('My World 2.0', 'Justin Bieber', NULL, '2010-05-13'),
	('Believe', 'Justin Bieber', 'Trending', '2012-02-14');

INSERT INTO song
	(album_id, song_name, song_duration, song_price, song_genre)
VALUES
	-- 25
	(1, 'Hello', '04:55', 3.50, 'Pop'),
	(1, 'When We Were Young', '04:50', 3.50, 'Pop'),
	(1, 'Million Years Ago', '03:47', 3.50, 'Jazz'),
	(1, 'All I Ask', '04:32', 3.50, 'Classical'),
	-- Purpose	
	(2, 'I Will Show You', '03:25', 3.00, 'Pop'),
	(2, 'What Do You Mean?', '03:25', 3.00, 'Hip-Hop'),
	(2, 'Sorry', '03:20', 3.00, 'RnB'),
	(2, 'Love Yourself', '03:53', 3.00, 'Pop'),
	-- The Piano Guys
	(3, 'Over the Rainbow, Simple Gifts', '03:44', 4.00, 'Classical'),
	(3, 'Beethoven 5 Secrets', '05:09', 4.00, 'Classical'),
	(3, 'A Thousand Years', '04:36', 4.00, 'Classical'),
	(3, 'Peponi', '04:10', 4.00, 'Classical'),
	-- The Marshall Mathers LP 2
	(4, 'The Monster', '04:10', 3.00, 'Hip-Hop'),
	(4, 'Rap God', '06:03', 3.00, 'Electric'),
	(4, 'Berzerk', '03:58', 3.00, 'Rock'),
	-- Nothing But the Best
	(5, 'Fly Me To the Moon', '02:27', 3.50, 'Jazz'),
	(5, 'My Way', '04:36', 3.50, 'Jazz'),
	(5, 'Strangers In the Night', '02:44', 3.50, 'Jazz'),
	-- Thriller
	(6, 'Thriller', '05:57', 4.00, 'RnB'),
	(6, 'Beat It', '04:18', 4.00, 'Hip-Hop'),
	(6, 'Billie Jean', '04:54', 4.00, 'Jazz'),
	-- Confident
	(7, 'Confident', '04:22', 4.00, 'Hip-Hop'),
	-- Blackstar
	(8, 'Blackstar', '09:57', 3.50, 'Rock'),
	(8, 'Lazarus', '06:22', 3.50, 'Electric'),
	(8, 'Dollar Days', '04:44', 3.50, 'RnB'),
	(8, 'I Cannot Give Everything Away', '05:47', 3.50, 'Hip-Hop'),
	-- Girl On Fire
	(9, 'Girl On Fire', '04:30', 4.00, 'RnB'),
	(9, 'Tears Always Win', '03:59', 4.00, 'RnB'),
	(9, 'Brand New Me', '03:53', 4.00, 'RnB'),
	-- Under The Mistletoe
	(10, 'Fa La La', '03:55', 3.00, 'RnB'),
	-- Love, Marriage & Divorce
	(11, 'Hurt You', '04:10', 3.00, 'RnB'),
	(11, 'Where Did We Go Wrong', '03:37', 3.00, 'Rock'),
	(11, 'Reunited', '03:18', 3.00, 'Electric'),
	(11, 'I Wish', '03:03', 3.00, 'RnB'),
	-- Night Visions
	(12, 'Radioactive', '03:06', 3.50, 'Rock'),
	(12, 'Demons', '02:57', 3.50, 'Rock'),
	(12, 'Its Time', '04:00', 3.50, 'Classical'),
	-- Does This Look Infected?
	(13, 'The Hell Song', '03:18', 4.00, 'Rock'),
	(13, 'Over My Head, Better Off Dead', '02:29', 4.00, 'Rock'),
	(13, 'Still Waiting', '02:38', 4.00, 'Rock'),
	(13, 'Thanks for Nothing', '03:04', 4.00, 'Rock'),
	-- My World 2.0
	(14, 'Where Are You Now', '03:45', 3.00, 'RnB'),
	-- Believe
	(15, 'As Long As You Love Me', '04:11', 4.00, 'Electric'),
	(15, 'Beauty And A Beat', '03:32', 4.00, 'Rock');

INSERT INTO format
	(format_of_song, format_price)
VALUES
	('mp3', 1.15),
	('wma', 1.10),
	('wav', 1.00);

-- album_rating
INSERT INTO review
	(user_id, album_id, review_rating, review_comment)
VALUES
	(1, 12, 4.0, 'Great album, love it.'),
	(7, 9, 5.0, 'One of the best album!'),
	(4, 1, 1.0, 'Worst album ever!'),
	(6, 11, 4.0, 'Awesome~~'),
	(7, 9, 3.0, 'So so..'),
	(1, 2, 4.0, 'Like it!'),
	(2, 2, 4.5, 'Well done!'),
	(5, 3, 2.5, 'A waste of money!'),
	(8, 11, 3.0, 'OK...'),
	(7, 2, 4.2, 'One of the best albums!'),
	(4, 7, 3.8, 'Not bad.'),
	(1, 4, 4.1, 'Just like it.'),
	(2, 5, 5.0, 'Worth it!'),
	(4, 5, 4.8, 'Nice album for collection.'),
	(6, 9, 4.1, 'What an album!'),
	(2, 6, 3.6, 'Still has space to improve.');

-- song_rating
INSERT INTO review
	(user_id, song_id, review_rating, review_comment)
VALUES
	(3, 36, 3.0, 'This song is epic.'),
	(6, 23, 4.0, 'Addictive song.'),
	(6, 9, 5.0, 'This song releases my soul!'),
	(2, 5, 2.0, 'Lame song.'),
	(7, 18, 5.0, 'It gives me goosebumps!'),
	(2, 3, 4.7, 'My favourite song!'),
	(9, 19, 5.0, 'A must listen song this year!'),
	(5, 18, 4.5, 'Addicted to this song.'),
	(4, 11, 3.0, 'So so...'),
	(1, 4, 2.0, 'Waste of money...'),
	(1, 9, 4.2, 'Like the chorus part!'),
	(8, 1, 4.4, 'Amazing!!'),
	(4, 2, 4.5, 'Just wow.'),
	(9, 6, 3.0, 'OK..');

INSERT INTO order
	(order_date, order_quantity, order_payment_method, order_card_num, order_tax, user_id)
VALUES
	('2012-02-04', 4, 'Master', '5571200428576225', 1.06, 9),
	('2015-01-29', 3, 'Master', '1568692387368551', 1.06, 5),
	('2014-02-01', 1, 'Master', '4388997619380775', 1.06, 9),
	('2015-05-21', 2, 'Visa', '5912626632056525', 1.06, 4),
	('2011-09-20', 5, 'CIMB Clicks', '0391325125792567', 1.06, 8),
	('2013-06-02', 3, 'CIMB Clicks', '2108903411664564', 1.06, 2),
	('2012-06-04', 3, 'Maybank2u', '1665777678804642', 1.06, 6),
	('2015-09-20', 2, 'Maybank2u', '1384840526804208', 1.06, 1),
	('2016-01-08', 3, 'Visa', '5869674929411283', 1.06, 3),
	('2014-07-01', 5, 'Paypal', '7593688480304381', 1.06, 6),
	('2015-05-22', 3, 'Master', '5571200428576225', 1.06, 9),
	('2015-09-09', 4, 'Visa', '5912626632056525', 1.06, 4),
	('2015-12-12', 2, 'CIMB Clicks', '0391325125792567', 1.06, 8),
	('2016-01-10', 3, 'Maybank2u', '1665777678804642', 1.06, 6),
	('2016-01-15', 1, 'Visa', '5869674929411283', 1.06, 3),
	('2016-01-22', 4, 'Maybank2u', '1384840526804208', 1.06, 1),
	('2016-01-25', 2, 'Maybank2u', '1384840526804208', 1.06, 1),
	('2016-02-03', 1, 'CIMB Clicks', '0391325125792567', 1.06, 8);

INSERT INTO order_detail
	(order_id, album_id, format_id)
VALUES
	-- order_id = 1
	(1, 3, 1),
	(1, 6, 2),
	(1, 7, 1),
	(1, 9, 1),
	-- order_id = 2
	(2, 4, 2),
	(2, 6, 1),
	(2, 5, 2),
	-- order_id = 3
	(3, 2, 2),
	-- order_id = 4
	(4, 2, 2),
	(4, 10, 3),
	-- order_id = 5
	(5, 1, 1),
	(5, 2, 1),
	(5, 4, 3),
	(5, 9, 2),
	(5, 11, 2),
	-- order_id = 6
	(6, 5, 3),
	(6, 6, 1),
	(6, 8, 2),
	-- order_id = 7
	(7, 3, 1),
	(7, 6, 2),
	(7, 7, 2),
	-- order_id = 8
	(8, 6, 2),
	(8, 9, 2),
	-- order_id = 9
	(9, 2, 1),
	(9, 3, 1),
	(9, 5, 2),
	-- order_id = 10
	(10, 1, 1),
	(10, 5, 1),
	(10, 6, 1),
	(10, 9, 3),
	(10, 10, 2),
	-- order_id = 11
	(11, 5, 1),
	(11, 6, 1),
	(11, 2, 2),
	-- order_id = 12
	(12, 3, 3),
	(12, 8, 2),
	(12, 7, 2),
	(12, 7, 1),
	-- order_id = 13
	(13, 3, 1),
	(13, 8, 3),
	-- order_id = 14
	(14, 5, 2),
	(14, 1, 3),
	(14, 3, 2),
	-- order_id = 15
	(15, 8, 1),
	-- order_id = 16
	(16, 7, 2),
	(16, 4, 3),
	(16, 5, 3),
	(16, 2, 2),
	-- order_id = 17
	(17, 8, 3),
	(17, 6, 2);

SELECT * FROM user; 
SELECT * FROM album; 
SELECT * FROM song; 
SELECT * FROM format;
SELECT * FROM review; 
SELECT * FROM order; 
SELECT * FROM order_detail;

--	/---------------------/
--	/ IV. CREATE TRIGGERS /
--	/---------------------/

---- #1: Update album_price
CREATE TRIGGER update_album_price
AFTER INSERT ON song
FOR EACH ROW MODE DB2SQL
	UPDATE album
	SET album_price = 
		(SELECT DISTINCT song_price FROM song WHERE album.album_id = song.album_id) *
		(SELECT COUNT(song_id) FROM song WHERE album.album_id = song.album_id);

CREATE TRIGGER update_album_price2
AFTER UPDATE OF song_price ON song
FOR EACH ROW MODE DB2SQL
	UPDATE album
	SET album_price = 
		(SELECT DISTINCT song_price FROM song WHERE album.album_id = song.album_id) *
		(SELECT COUNT(song_id) FROM song WHERE album.album_id = song.album_id);

-- test trigger #1 (after update)
UPDATE song
SET song_price = 3.80
WHERE song.album_id = 1;

SELECT * FROM album;

---- #2: Update song_rating
CREATE TRIGGER update_song_rating
AFTER INSERT ON review
FOR EACH ROW MODE DB2SQL
	UPDATE song
	SET song_rating = 
		(SELECT AVG(review_rating) FROM review WHERE song.song_id = review.song_id);

CREATE TRIGGER update_song_rating2
AFTER UPDATE OF review_rating ON review
FOR EACH ROW MODE DB2SQL
	UPDATE song
	SET song_rating = 
		(SELECT AVG(review_rating) FROM review WHERE song.song_id = review.song_id);

-- test trigger #2 (after insert)
INSERT INTO review
	(user_id, song_id, review_rating, review_comment)
VALUES
	(9, 20, 5.0, 'Legendary song!');

SELECT * FROM song;

---- #3: Update album_rating
CREATE TRIGGER update_album_rating
AFTER INSERT ON review
FOR EACH ROW MODE DB2SQL
	UPDATE album
	SET album_rating = 
		(SELECT AVG(review_rating) FROM review WHERE album.album_id = review.album_id);

CREATE TRIGGER update_album_rating2
AFTER UPDATE OF review_rating ON review
FOR EACH ROW MODE DB2SQL
	UPDATE album
	SET album_rating = 
		(SELECT AVG(review_rating) FROM review WHERE album.album_id = review.album_id);

-- test trigger #3 (after insert)
INSERT INTO review
	(user_id, album_id, review_rating, review_comment)
VALUES
	(9, 6, 5.0, 'My favourite album!');

SELECT * FROM album;

---- #4: Update order_price
CREATE TRIGGER update_order_price
AFTER INSERT ON order_detail
FOR EACH ROW MODE DB2SQL
	UPDATE order_detail
	SET order_price = 
		(SELECT album_price FROM album WHERE album.album_id = order_detail.album_id) * 
		(SELECT format_price FROM format WHERE format.format_id = order_detail.format_id);

---- #5: Update order_invoice
CREATE TRIGGER update_order_invoice
AFTER INSERT ON order_detail
FOR EACH ROW MODE DB2SQL
	UPDATE order
	SET order_invoice = 
		order_tax * 
		(SELECT SUM(order_price) FROM order_detail WHERE order.order_id = order_detail.order_id); 

-- Note: Used in conjuction with procedure #1 discount
CREATE TRIGGER update_order_invoice2
AFTER UPDATE OF order_tax ON order
FOR EACH ROW MODE DB2SQL
	UPDATE order
	SET order_invoice = 
		order_tax * 
		(SELECT SUM(order_price) FROM order_detail WHERE order.order_id = order_detail.order_id);

-- test trigger #4 and #5 (after insert)
INSERT INTO order_detail 
	(order_id, album_id, format_id) 
VALUES 
	-- order_id = 18 
	(18, 5, 2);

SELECT * FROM order_detail;
SELECT * FROM order;

--	/------------/
--	/ V. QUERIES /
--	/------------/

---- #1: List albums with four songs.
-- aggregate function, group by with having clause
SELECT album_name, COUNT(song_id) AS num_of_songs
FROM album, song
WHERE album.album_id = song.album_id
GROUP BY album_name
HAVING COUNT(song_id) = 4;

---- #2: List every song genre and number of songs associated with each.
-- aggregate function
SELECT song_genre, COUNT(song_id) AS num_of_songs
FROM song
GROUP BY song_genre;

---- #3: List albums with its average song rating higher than or equal to four.
-- aggregate function, group by with having clause, extra (cast and round)
SELECT album_name, CAST(ROUND(AVG(song_rating), 2) AS DECIMAL(2,1)) AS AVG_song_rating_of_album
FROM album, song
WHERE album.album_id = song.album_id
GROUP BY album_name
HAVING AVG(song_rating) >= 4;

---- #4: List the most recent five orders from John.
-- aggregate function, nested query, extra (cast, round and fetch first n rows only)
SELECT order_date, album_name AS album_purchased, CAST(ROUND((order_price * order_tax),2) AS DECIMAL(5,2)) AS final_price
FROM order, album, order_detail
WHERE order_detail.album_id = album.album_id
AND order_detail.order_id = order.order_id
AND user_id = (SELECT user_id from user WHERE user_name = 'John' AND user.user_id = order.user_id)
ORDER BY order_date DESC
FETCH FIRST 5 ROWS ONLY;

---- #5: List songs rated and ratings given by Brian.
-- nested query, extra (table alias)
SELECT song_name AS rated_song, review_rating AS rating_given, user_name AS rated_by
FROM song, review, user U
WHERE U.user_id = review.user_id 
AND review.song_id  = song.song_id
AND U.user_id = (SELECT user_id FROM user WHERE user_name = 'Brian');

---- #6: Update username.
-- nested query
UPDATE user
SET user_name = 'Mingo'
WHERE user_id = (SELECT user_id FROM user WHERE user_name = 'Ming');

SELECT * FROM user;

---- #7: Update review rating and comment.
-- nested query
UPDATE review
SET review_rating = 4.0, review_comment = 'Like it after listened n times.'
WHERE user_id = (SELECT user_id FROM user WHERE user_name = 'John')
AND song_id = (SELECT song_id FROM review WHERE song_id = 4);

---- #8: List albums' popularity by purchase rate.
-- aggregate function, extra (cast and count)
SELECT album_name, (CAST(((COUNT(order_detail.album_id))/
(SELECT CAST(COUNT(album_id) AS DECIMAL(4,2)) FROM order_detail)) AS DECIMAL(4,2))* 100) AS purchase_percent
FROM order_detail, album
WHERE order_detail.album_id = album.album_id
GROUP BY album_name
ORDER BY purchase_percent DESC;

--	/------------------/
--	/ VI. CREATE VIEWS /
--	/------------------/

---- #1: List songs with rating higher than or equal to four.
CREATE VIEW top_rate_songs AS
	SELECT song_name, album_name, song_rating
	FROM song, album
	WHERE song.album_id = album.album_id
	AND song_rating >= 4;

-- test view #1
SELECT * FROM top_rate_songs;

---- #2: List users with their total invoice.
CREATE VIEW transaction_history AS
	SELECT user_name AS name, COUNT(album_id) AS total_album_purchased, SUM(order_invoice) AS total_price
	FROM order, user, order_detail
	WHERE user.user_id = order.user_id
	AND order_detail.order_id = order.order_id
	GROUP BY user_name;

-- test view #2
SELECT * FROM transaction_history;

--	/------------------------/
--	/ VII. CREATE PROCEDURES /
--	/------------------------/

---- #1: Update tax as a discount for customers that purchased more than or equal to three albums.
-- Note: Used in conjunction with trigger #6 update_order_invoice2
CREATE PROCEDURE discount(IN discount_index DECIMAL(3,2))
LANGUAGE SQL
BEGIN
	UPDATE order
	SET order_tax = order_tax - discount_index
	WHERE order_quantity >= 3;
END@

-- test procedure #1
CALL discount(0.06);
SELECT order_id, order_quantity, order_tax, order_invoice
FROM order;

---- #2: Update an album's category.
CREATE PROCEDURE update_category(IN category VARCHAR(10), albumID INT)
BEGIN
	IF(category = 'New') THEN 
		UPDATE album
		SET album_category = 'New'
		WHERE album_id = albumID;
	ELSE
		UPDATE album
		SET album_category = 'Trending'
		WHERE album_id = albumID;
	END IF;
END@

-- test procedure #2
CALL update_category('Trending', 4);
SELECT * FROM album;

--	/---------------------/
--	/ VIII. DROP DATABASE /
--	/---------------------/

CONNECT RESET;
DROP DATABASE msicstor;