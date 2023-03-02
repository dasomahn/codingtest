-- 진료과별 총 예약 횟수 출력하기
SELECT mcdp_cd as '진료과코드' , COUNT(*) as '5월예약건수'
FROM APPOINTMENT
WHERE YEAR(apnt_ymd) = 2022 and MONTH(apnt_ymd) = 5
GROUP BY mcdp_cd
ORDER BY 5월예약건수, 진료과코드

-- 고양이와 개는 몇 마리 있을까
SELECT animal_type, COUNT(*) as count
FROM ANIMAL_INS
GROUP BY animal_type
ORDER BY animal_type

-- 동명 동물 수 찾기
SELECT NAME, COUNT(NAME) as 'COUNT'
FROM ANIMAL_INS
GROUP BY NAME
HAVING COUNT > 1
ORDER BY NAME

-- 입양 시각 구하기(1)
SELECT HOUR(datetime) as HOUR, COUNT(*) as COUNT
FROM ANIMAL_OUTS
GROUP BY HOUR(datetime)
HAVING HOUR BETWEEN 9 AND 19
ORDER BY HOUR

-- 가격대 별 상품 개수 구하기
SELECT TRUNCATE(PRICE, -4) as price_group, COUNT(*) as products
FROM PRODUCT
GROUP BY price_group
ORDER BY price_group

-- 성분으로 구분한 아이스크림 총 주문량
SELECT ingredient_type, SUM(total_order) as total_order
FROM FIRST_HALF as h
JOIN ICECREAM_INFO as i on h.flavor = i.flavor
# JOIN ICECREAM_INFO using (flavor)
GROUP BY ingredient_type
ORDER BY total_order

-- 자동차 종류 별 특정 옵션이 포함된 자동차 수 구하기
SELECT car_type, count(*) as CARS
FROM CAR_RENTAL_COMPANY_CAR
WHERE options LIKE '%시트%'
# WHERE options REGEXP '통풍시트|열선시트|가죽시트'
GROUP BY car_type
ORDER BY car_type