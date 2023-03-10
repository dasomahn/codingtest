-- 대여 기록이 존재하는 자동차 리스트 구하기
SELECT DISTINCT car_id
FROM CAR_RENTAL_COMPANY_CAR 
NATURAL JOIN CAR_RENTAL_COMPANY_RENTAL_HISTORY
WHERE car_type = '세단' and MONTH(start_date) = 10
ORDER BY car_id DESC

-- 조건별로 분류하여 주문상태 출력하기
SELECT order_id, product_id, DATE_FORMAT(out_date, '%Y-%m-%d') as out_date,
    CASE
        WHEN out_date is NULL THEN '출고미정'
        WHEN out_date <= '2022-05-01' THEN '출고완료'
        ELSE '출고대기'
    END as 출고여부
FROM FOOD_ORDER
ORDER BY order_id

-- 오랜 기간 보호한 동물(2)
SELECT animal_id, o.name
FROM ANIMAL_OUTS as o
JOIN ANIMAL_INS as i USING (animal_id)
ORDER BY (o.datetime - i.datetime) DESC
LIMIT 2
