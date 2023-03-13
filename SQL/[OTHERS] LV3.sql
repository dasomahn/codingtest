-- 2021 Dev-Matching: 웹 백엔드 개발자(상반기) > 헤비 유저가 소유한 장소
-- 풀이 1 (subquery)
SELECT *
FROM PLACES
WHERE host_id in (
    SELECT host_id
    FROM PLACES
    GROUP BY host_id
    HAVING COUNT(*) > 1
)
ORDER BY id

-- 풀이 2 (self join)
SELECT DISTINCT A.*
FROM PLACES A
JOIN PLACES B ON A.ID <> B.ID AND A.HOST_ID = B.HOST_ID
ORDER BY id