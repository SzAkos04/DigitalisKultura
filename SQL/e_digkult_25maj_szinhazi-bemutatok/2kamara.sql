SELECT
	szinhaz.nev,
    szinhaz.szekhely
FROM
	szinhaz
WHERE
    szinhaz.belfoldi = 1
	AND szinhaz.nev LIKE "%Kamara%";
