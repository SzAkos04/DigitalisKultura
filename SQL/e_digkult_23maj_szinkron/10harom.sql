SELECT
	szinkron.szinesz,
    szinkron.hang,
    COUNT(*) AS filmek_szama
FROM
	szinkron
GROUP BY
	szinkron.szinesz,
    szinkron.hang
HAVING
	filmek_szama >= 3
ORDER BY filmek_szama DESC;