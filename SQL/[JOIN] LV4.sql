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