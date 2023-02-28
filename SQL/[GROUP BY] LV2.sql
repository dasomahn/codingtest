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