-- 보호소에서 중성화한 동물
SELECT i.animal_id, i.animal_type, i.name
FROM ANIMAL_INS as i
JOIN ANIMAL_OUTS as o ON i.animal_id = o.animal_id
WHERE sex_upon_intake != sex_upon_outcome

-- 그룹별 조건에 맞는 식당 목록 출력하기
SELECT member_name, review_text, DATE_FORMAT(review_date, '%Y-%m-%d')
FROM MEMBER_PROFILE as m
JOIN REST_REVIEW as r ON m.member_id = r.member_id
WHERE m.member_id = (
    SELECT member_id
    FROM REST_REVIEW
    GROUP BY member_id
    ORDER BY COUNT(*) DESC
    LIMIT 1
)
ORDER BY review_date, review_text

-- 5월 식품들의 총매출 조회하기
SELECT p.PRODUCT_ID, PRODUCT_NAME, SUM(PRICE * AMOUNT) as TOTAL_PRICE
FROM FOOD_PRODUCT as p
JOIN FOOD_ORDER as o on p.product_id = o.product_id
WHERE YEAR(PRODUCE_DATE) = 2022 and MONTH(PRODUCE_DATE) = 5
GROUP BY p.product_id
ORDER BY TOTAL_PRICE DESC, p.product_id

-- 주문량이 많은 아이스크림들 조회하기
SELECT j.flavor
FROM FIRST_HALF as f
JOIN JULY as j on f.flavor = j.flavor
GROUP BY j.flavor
ORDER BY j.total_order + SUM(f.total_order) DESC
LIMIT 3

-- 특정 기간동안 대여 가능한 자동차들의 대여비용 구하기
SELECT *
FROM (
    SELECT CAR_ID, c.CAR_TYPE, FLOOR(daily_fee * (100 - discount_rate) * 0.3) as FEE
    FROM CAR_RENTAL_COMPANY_CAR as c
    JOIN CAR_RENTAL_COMPANY_DISCOUNT_PLAN as p on c.car_type = p.car_type
    WHERE car_id not in (
            SELECT car_id
            FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
            WHERE (start_date between '2022-11-01' and '2022-11-30')
                or (end_date between '2022-11-01' and '2022-11-30')
                or (start_date < '2022-11-01' and '2022-11-30' < end_date)
        )
        and c.car_type in ('세단', 'SUV')
        and duration_type = '30일 이상'
) as t
WHERE 500000 <= fee and fee < 2000000
ORDER BY fee DESC, car_type, car_id DESC