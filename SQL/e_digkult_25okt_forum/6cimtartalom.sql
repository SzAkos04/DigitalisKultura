SELECT DISTINCT
    felhasznalo.veznev,
    felhasznalo.utonev,
    uzenet.tartalom,
    uzenet.kuldido
FROM
    uzenet
INNER JOIN
    felhasznalo ON uzenet.f_id = felhasznalo.id
INNER JOIN
    hirfolyam ON uzenet.tartalom LIKE CONCAT('%', hirfolyam.megnevezes, '%')
ORDER BY
    uzenet.kuldido ASC;
