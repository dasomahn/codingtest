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

-- 카테고리 별 도서 판매량 집계하기
SELECT category, SUM(sales) as TOTAL_SALES
FROM BOOK
JOIN BOOK_SALES using (book_id)
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 1
GROUP BY category
ORDER BY category

-- 즐겨찾기가 가장 많은 식당 정보 출력하기
SELECT food_type, rest_id, rest_name, favorites
FROM (
    SELECT *, 
    RANK() OVER(PARTITION BY food_type ORDER BY favorites DESC) as r
    FROM REST_INFO
) AS T
WHERE r = 1
ORDER BY food_type DESC

-- 자동차 대여 기록에서 대여중 / 대여 가능 여부 구분하기
-- 풀이 1
SELECT DISTINCT CAR_ID,
    IF (CAR_ID in (
        SELECT CAR_ID
        FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
        WHERE '22-10-16' BETWEEN START_DATE and END_DATE), '대여중', '대여 가능') as AVAILABILITY
FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY   
ORDER BY CAR_ID DESC

-- 풀이 2
SELECT CAR_ID,
    IF(SUM(IF('2022-10-16' BETWEEN START_DATE and END_DATE, 1, 0)) = 1, '대여중', '대여 가능') as AVAILABILITY
FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
GROUP BY CAR_ID
ORDER BY CAR_ID DESC