-- 대여 횟수가 많은 자동차들의 월별 대여 횟수 구하기
-- 풀이 1 (GROUP BY)
SELECT MONTH(start_date) as MONTH, car_id, count(*) as RECORDS 
FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
WHERE car_id in (
    SELECT car_id 
    FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
    WHERE YEAR(start_date) = 2022 and MONTH(start_date) in (8, 9, 10)
    GROUP BY car_id
    HAVING COUNT(*) >= 5
)
and YEAR(start_date) = 2022 and MONTH(start_date) in (8, 9, 10)
GROUP BY YEAR(start_date), MONTH(start_date), car_id
ORDER BY MONTH, car_id DESC

-- 풀이 2 (Window 함수)
SELECT MONTH, CAR_ID, RECORDS
FROM (
    SELECT car_id,
    MONTH(start_date) as MONTH,
    COUNT(*) as RECORDS,
    SUM(COUNT(*)) OVER (PARTITION BY car_id) as TOTAL_RECORDS
    FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
    WHERE YEAR(start_date) = 2022 and MONTH(start_date) in (8, 9, 10)
    GROUP BY YEAR(start_date), MONTH(start_date), car_id
) as T
WHERE TOTAL_RECORDS >= 5
ORDER BY MONTH, car_id DESC