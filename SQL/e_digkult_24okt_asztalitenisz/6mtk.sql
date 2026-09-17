SELECT
    jatekos.nev
FROM
    bajnok
INNER JOIN
    jatekos ON bajnok.jatekos_id = jatekos.id
INNER JOIN
    egyesulet ON bajnok.egyesulet_id = egyesulet.id
WHERE
    egyesulet.nev = "MTK"
GROUP BY
    jatekos.nev,
    jatekos.neme
ORDER BY
    jatekos.neme,
    jatekos.nev;