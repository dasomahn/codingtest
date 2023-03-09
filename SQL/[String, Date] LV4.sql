-- 자동차 대여 기록 별 대여 금액 구하기
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