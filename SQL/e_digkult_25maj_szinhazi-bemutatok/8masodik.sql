SELECT
	szinhaz.szekhely,
    COUNT(*) AS szam
FROM
	szinhaz
WHERE
	szinhaz.belfoldi = 1
GROUP BY
	szinhaz.szekhely 
ORDER BY szam DESC
LIMIT 1 OFFSET 1;
