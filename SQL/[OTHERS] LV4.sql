-- SELECT > 서울에 위치한 식당 목록 출력하기
SELECT rest_id, rest_name, food_type, favorites, address, ROUND(AVG(review_score), 2) as score
FROM REST_INFO
NATURAL JOIN REST_REVIEW
WHERE LEFT(address, 2) = '서울'
GROUP BY rest_name
ORDER BY score DESC, favorites DESC

-- SELECT > 오프라인/온라인 판매 데이터 통합하기
-- 풀이1 (FULL OUTER JOIN)
SELECT DATE_FORMAT(sales_date, '%Y-%m-%d') as date, product_id, user_id, sales_amount
FROM ONLINE_SALE
NATURAL LEFT JOIN OFFLINE_SALE
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 3

UNION

SELECT DATE_FORMAT(sales_date, '%Y-%m-%d') as date, product_id, NULL as user_id, sales_amount
FROM ONLINE_SALE
NATURAL RIGHT JOIN OFFLINE_SALE
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 3

ORDER BY date, product_id, user_id

-- 풀이2 (UNION)
SELECT DATE_FORMAT(sales_date, '%Y-%m-%d') as date, product_id, user_id, sales_amount
FROM ONLINE_SALE
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 3

UNION

SELECT DATE_FORMAT(sales_date, '%Y-%m-%d') as date, product_id, NULL, sales_amount
FROM OFFLINE_SALE
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 3

ORDER BY date, product_id, user_id

-- String, Date > 자동차 대여 기록 별 대여 금액 구하기
-- 풀이 1
SELECT history_id, FLOOR(dur * daily_fee * (100 - IFNULL(discount_rate, 0)) / 100) as fee
FROM (
    SELECT *,
        IF(dur >= 90, '90일 이상',
            IF(dur >= 30, '30일 이상',
               IF(dur >= 7, '7일 이상', null)
              )
        ) as dur_type
    FROM CAR_RENTAL_COMPANY_CAR
    NATURAL JOIN (
        SELECT history_id, car_id,
            DATEDIFF(end_date, start_date) + 1 as dur
        FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
    ) as t1
    WHERE car_type = '트럭'
) as t2
LEFT OUTER JOIN CAR_RENTAL_COMPANY_DISCOUNT_PLAN as p
on t2.car_type = p.car_type and t2.dur_type = p.duration_type
ORDER BY fee DESC, history_id DESC

-- 풀이 2
SELECT history_id, FLOOR((DATEDIFF(end_date, start_date) + 1) * daily_fee * (100 - IFNULL(discount_rate, 0)) / 100) as fee
FROM CAR_RENTAL_COMPANY_CAR as c
NATURAL JOIN CAR_RENTAL_COMPANY_RENTAL_HISTORY
LEFT OUTER JOIN CAR_RENTAL_COMPANY_DISCOUNT_PLAN as p
on c.car_type = p.car_type and
    duration_type = 
        CASE
            WHEN DATEDIFF(end_date, start_date) + 1 >= 90 THEN '90일 이상'
            WHEN DATEDIFF(end_date, start_date) + 1 >= 30 THEN '30일 이상'
            WHEN DATEDIFF(end_date, start_date) + 1 >= 7 THEN '7일 이상'
        END
WHERE c.car_type = '트럭'
ORDER BY fee DESC, history_id DESC