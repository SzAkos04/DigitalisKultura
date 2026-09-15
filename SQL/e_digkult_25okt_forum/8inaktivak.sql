SELECT
    felhasznalo.veznev,
    felhasznalo.utonev
FROM
    felhasznalo
LEFT JOIN
    uzenet ON felhasznalo.id = uzenet.f_id
WHERE
    felhasznalo.utolso < '2010-01-01'
GROUP BY
    felhasznalo.id,
    felhasznalo.veznev,
    felhasznalo.utonev
HAVING
    COUNT(uzenet.f_id) = 0;
