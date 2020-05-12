# change bits
function transformBits(n){
    i = 8 
    ans = 0
    while( i > 0)
    {
        ans = lshift(ans, 1)
        ans = ans + and(n, 1)
        n = rshift(n, 1)
        i = i - 1
    }
    return ans
}

# Hex to Dec
function toDecimal(tmp){
    return strtonum("0x"tmp)
}


{
    for (j = 1; j <= NF; j++) {
        grades[j] = $j
        grades2[j] = toDecimal(grades[j])
        grades3[j] = transformBits(grades2[j])
        printf("%02x ", grades3[j])
    }
    printf("\n")
}

