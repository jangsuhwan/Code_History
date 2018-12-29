<h1> RSA.cpp <h1>
<h2> 30-bit triple RSA & Digital Signature Implementation </h2>
<h3> : RSA 암호화를 구현하여 직접 암호화, 복호화를 수행하고 RSA 기반의 digital signature 구현 <h3>

- Key Greneration
  - n = p * q * r (각 10bit)
- p, q, r, e는 rand, srand와 같은 일반 random number generator 사용
- 성능 향상을 위한 다음과 같은 알고리즘들을 구현
  - Squanre and Multiply Algorithm
  - Miller-Rabin Primality Test
  - Extended Euclidean Algorithm
  - Chinese Remainder Theorem
  
  

<h1> AES.cpp </h1>
<h2> AES 구현 </h2>

- Irreducible Polynomials : X^8 + X^6 + X^5 + X^3 + 1
- Galois Field 덧셈, 곱셈,, 역원 연산 함수 구현
- RC, Key Expansion 구현
- S-Box, Inverse S-Box 구현(상수 : 0x15)
- Substitute Bytes, Shift Row, Mix Columns, Add Round Key 구현(Inverse 포함
