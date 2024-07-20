while true; do
    python gen.py > in
    ./a < in > 1.out
    ./force < in > 2.out
    if diff 1.out 2.out -Z; then
        printf "# Accepted\n"
    else 
        # notify-send 'Wrong Answer'
        break
    fi
done

# cnt=1
# while true; do
#     ./checker ./secret/$cnt.in ./secret/$cnt.ans ./secret/$cnt.ans 
#     ((cnt++))
# done
