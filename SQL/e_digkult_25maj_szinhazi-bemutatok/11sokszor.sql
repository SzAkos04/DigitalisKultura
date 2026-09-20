SELECT 
	(SELECT COUNT(*)
    FROM szinhaz
    WHERE szinhaz.szekhely = "Budapest")
    /
    (SELECT COUNT(*)
    FROM szinhaz
    WHERE szinhaz.szekhely <> "Budapest");
