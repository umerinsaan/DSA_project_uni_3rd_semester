#include "ArithmeticExpressionWidget.h"

#define ull unsigned long long
#define ll long long

ArithmeticExpressionWidget::ArithmeticExpressionWidget(QWidget *parent)
    : QWidget(parent)
{
    // Create input field (QTextEdit)
    inputTextEdit = new QTextEdit(this);
    inputTextEdit->setFont({"Arial",16});

    this->resultTextEdit = new QTextEdit(this);
    this->resultTextEdit->setFont({"Arial",16});


    // Create solve button
    solveButton = new QPushButton("Solve", this);
    connect(solveButton, &QPushButton::clicked, this, &ArithmeticExpressionWidget::solveArithmeticExpression);

    // Create result label
    resultLabel = new QLabel("Result: ", this);
    resultLabel->setFont({"Arial",16});

    // Create Go Back button
    goBackButton = new QPushButton("Go Back", this);
    connect(goBackButton, &QPushButton::clicked, this, &ArithmeticExpressionWidget::goBack);

    // Set up the layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(inputTextEdit);
    layout->addWidget(solveButton);
    layout->addWidget(resultLabel);
    layout->addWidget(this->resultTextEdit);
    layout->addStretch(1);

    setLayout(layout);
}

void ArithmeticExpressionWidget::solveArithmeticExpression()
{

    this->solveButton->setText("Solving...");


    QString infix = this->inputTextEdit->toPlainText();
    std::string postfix = this->infixToPostfix(infix);

    std::string ans ="NULL";
    if(postfix.length() > 0){
        std::cout<<"check"<<std::endl;
        std::cout<<postfix<<std::endl;

        ans = this->evaluatePostfix(postfix);
        std::cout<<"answer = "<<ans<<std::endl;
    }

    this->resultTextEdit->setText(QString::fromStdString(ans));
    this->solveButton->setText("Solve");

}

void ArithmeticExpressionWidget::goBack()
{
    // Emit a signal or call a function to handle going back to the previous page
    // For simplicity, we emit a signal here
    emit goBackClicked();
}

std::string ArithmeticExpressionWidget::infixToPostfix(QString& infix){
    std::stack<char> st;

    std::string inf = infix.toStdString();
    std::unordered_map<char, int> prec;
    prec['-'] = 1;
    prec['+'] = 1;
    prec['*'] = 2;
    prec['/'] = 2;
    prec['^'] = 3;

    std::string postfix = "";

    for(unsigned long long i = 0; i<inf.length() ; i++){
        if(inf[i] == ' ') continue;

        else if(inf[i] == '('){
            st.push(inf[i]);
        }

        else if(i < inf.length()-1 && inf[i] == '-' && inf[i+1] != ' '){

            while(i<inf.length() && inf[i]!= ' '){
                postfix.push_back(inf[i++]);
            }
            postfix.push_back(' ');
        }

        else if(inf[i] == '+' || inf[i] == '-' || inf[i] == '*' || inf[i] == '/' || inf[i] == '^'){
            while(!st.empty() && prec[inf[i]] <= prec[st.top()]){
                postfix.push_back(st.top());
                postfix.push_back(' ');
                st.pop();
            }
            st.push(inf[i]);
        }

        else if(inf[i] == ')'){
            while(!st.empty() && st.top() != '('){
                postfix.push_back(st.top());
                postfix.push_back(' ');
                st.pop();
            }
            st.pop();
        }

        else {
            while(i<inf.length() && infix[i] != ' '){
                postfix.push_back(inf[i++]);
            }
            i--;
            postfix.push_back(' ');
        }
    }

    while(!st.empty()){
        postfix.push_back(st.top());
        postfix.push_back(' ');
        st.pop();
    }

    if(postfix.back() == ' ') postfix.pop_back();

    return postfix;
}

std::string ArithmeticExpressionWidget::plus(std::string &a, std::string &b)
{
    removeTrailingZeroes(a);
    removeTrailingZeroes(b);

    ll dec_pos_a = findDecimalIndexAndRemove(a);
    ll dec_pos_b = findDecimalIndexAndRemove(b);

    ll p10_a = dec_pos_a == -1 ? 0 : a.length() - dec_pos_a;
    ll p10_b = dec_pos_b == -1 ? 0 : b.length() - dec_pos_b;

    ll max_p10 = std::max(p10_a, p10_b);

    if (dec_pos_a != -1 && dec_pos_b != -1)
    {
        ull diff_a = a.length() - dec_pos_a;
        ull diff_b = b.length() - dec_pos_b;

        if (diff_a > diff_b)
        {
            b.append(diff_a - diff_b, '0');
        }
        else if (diff_b > diff_a)
        {
            a.append(diff_b - diff_a, '0');
        }
    }
    else if (dec_pos_a == -1 && dec_pos_b != -1)
    {
        ull diff_b = b.length() - dec_pos_b;
        a.append(diff_b, '0');
    }
    else if (dec_pos_b == -1 && dec_pos_a != -1)
    {
        ull diff_a = a.length() - dec_pos_a;
        b.append(diff_a, '0');
    }

    std::string ans = "";

    int carry = 0;
    ull i = 0;
    for (i = 0; i < a.length() && i < b.length(); i++)
    {
        int x = a[a.length() - i - 1] - '0';
        int y = b[b.length() - i - 1] - '0';

        int z = x + y + carry;

        if (z > 9)
        {
            carry = z / 10;
            z = z % 10;
        }
        else
        {
            carry = 0;
        }

        char ch = z + '0';

        ans = ch + ans;
    }

    while (i < a.length())
    {
        int x = a[a.length() - i - 1] - '0';
        int z = x + carry;

        if (z > 9)
        {
            carry = z / 10;
            z = z % 10;
        }
        else
        {
            carry = 0;
        }

        char ch = z + '0';
        ans = ch + ans;
        i++;
    }

    while (i < b.length())
    {
        int x = b[b.length() - i - 1] - '0';
        int z = x + carry;

        if (z > 9)
        {
            carry = z / 10;
            z = z % 10;
        }
        else
        {
            carry = 0;
        }

        char ch = z + '0';
        ans = ch + ans;
        i++;
    }

    if (carry > 0)
    {
        char ch = carry + '0';
        ans = ch + ans;
    }

    ll ans_dec_pos = ans.length() - max_p10;

    if (ans_dec_pos > 0)
    {
        ans.insert(ans_dec_pos, 1, '.');
    }

    if (ans.back() == '.')
        ans.pop_back();

    return ans;
}

std::string ArithmeticExpressionWidget::subtract(std::string &a, std::string &b, bool isDivision)
{
    removeTrailingZeroes(a);
    removeTrailingZeroes(b);

    ll dec_pos_a = findDecimalIndexAndRemove(a);
    ll dec_pos_b = findDecimalIndexAndRemove(b);

    bool isNegative = false;

    if (dec_pos_a == -1 && dec_pos_b == -1)
    {
        if (b.length() > a.length())
        {
            isNegative = true;
        }
        else if (b.length() == a.length())
        {
            ull i = 0;
            while (i < a.length())
            {
                if (b[i] > a[i])
                {
                    isNegative = true;
                    break;
                }
                else if (b[i] < a[i])
                {
                    break;
                }
                i++;
            }
        }
    }

    else if (dec_pos_a != -1 && dec_pos_b == -1)
    {
        if (dec_pos_a < b.length())
        {
            isNegative = true;
        }
        else if (dec_pos_a == b.length())
        {
            ull i = 0;
            while (i < a.length())
            {
                if (b[i] > a[i])
                {
                    isNegative = true;
                    break;
                }
                else if (b[i] < a[i])
                {
                    break;
                }
                i++;
            }
        }
    }
    else if (dec_pos_b != -1 && dec_pos_a == -1)
    {
        if (dec_pos_b > a.length())
        {
            isNegative = true;
        }
        else if (dec_pos_b == a.length())
        {
            ull i = 0;
            while (i < a.length())
            {
                if (b[i] > a[i])
                {
                    isNegative = true;
                    break;
                }
                else if (b[i] < a[i])
                {
                    break;
                }
                i++;
            }
        }
    }
    else if (dec_pos_a != -1 && dec_pos_b != -1)
    {
        if (dec_pos_b > dec_pos_a)
        {
            isNegative = true;
        }
        else if (dec_pos_b == dec_pos_a)
        {
            ull i = 0;
            while (i < a.length())
            {
                if (b[i] > a[i])
                {
                    isNegative = true;
                    break;
                }
                else if (b[i] < a[i])
                {
                    break;
                }
                i++;
            }
        }
    }

    if (isNegative)
    {
        if(isDivision)
            return ""; // only when we subtract in divide function

        std::swap(a, b);
        std::swap(dec_pos_a, dec_pos_b);
    }

    ll p10_a = dec_pos_a == -1 ? 0 : a.length() - dec_pos_a;
    ll p10_b = dec_pos_b == -1 ? 0 : b.length() - dec_pos_b;

    ll max_p10 = std::max(p10_a, p10_b);

    if (dec_pos_a != -1 && dec_pos_b != -1)
    {
        ull diff_a = a.length() - dec_pos_a;
        ull diff_b = b.length() - dec_pos_b;

        if (diff_a > diff_b)
        {
            b.append(diff_a - diff_b, '0');
        }
        else if (diff_b > diff_a)
        {
            a.append(diff_b - diff_a, '0');
        }
    }
    else if (dec_pos_a == -1 && dec_pos_b != -1)
    {
        ull diff_b = b.length() - dec_pos_b;
        a.append(diff_b, '0');
    }
    else if (dec_pos_b == -1 && dec_pos_a != -1)
    {
        ull diff_a = a.length() - dec_pos_a;
        b.append(diff_a, '0');
    }

    std::string ans = "";

    int carry = 0;
    ull i = 0;

    for (i = 0; i < a.length() && i < b.length(); i++)
    {
        int x = a[a.length() - i - 1] - '0' - carry;
        int y = b[b.length() - i - 1] - '0';

        if (y > x)
        {
            x += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        int z = x - y;

        char ch = z + '0';

        ans = ch + ans;
    }

    while (i < a.length())
    {
        int num = a[a.length() - i - 1] - '0' - carry;
        if (num < 0)
        {
            num += 10;
            carry = 1;
            // num = num % 10;
        }
        else
        {
            carry = 0;
        }

        char ch = num + '0';

        ans = ch + ans;

        i++;
    }

    ll ans_dec_pos = ans.length() - max_p10;

    if (ans_dec_pos > 0)
    {
        ans.insert(ans_dec_pos, 1, '.');
    }

    if (ans.back() == '.')
        ans.pop_back();

    removeTrailingZeroes(ans);

    if (isNegative)
    {
        ans = '-' + ans;
    }

    if (ans == "")
        return "0";

    return ans;
}

std::string ArithmeticExpressionWidget::multiply(std::string &a, std::string &b)
{
    bool isNegative = false;

    if (a[0] == '-')
    {
        a.erase(0, 1);
        isNegative = !isNegative;
    }

    if (b[0] == '-')
    {
        b.erase(0, 1);
        isNegative = !isNegative;
    }

    if (a == "0" || b == "0")
        return "0";

    removeTrailingZeroes(a);
    removeTrailingZeroes(b);

    ll dec_pos_a = findDecimalIndexAndRemove(a);
    ll dec_pos_b = findDecimalIndexAndRemove(b);

    ll p10_a = dec_pos_a == -1 ? 0 : a.length() - dec_pos_a;
    ll p10_b = dec_pos_b == -1 ? 0 : b.length() - dec_pos_b;

    ull total_p10 = p10_a + p10_b;

    std::string ans = "";
    std::vector<int> res(a.length() + b.length(), 0);

    for (ull i = 0; i < b.length(); i++)
    {
        int x = b[b.length() - i - 1] - '0';

        for (ull j = 0; j < a.length(); j++)
        {
            int y = a[a.length() - j - 1] - '0';

            res[res.size() - (i + j) - 1] += x * y;
            res[res.size() - (i + j) - 2] += res[res.size() - (i + j) - 1] / 10;
            res[res.size() - (i + j) - 1] = res[res.size() - (i + j) - 1] % 10;
        }
    }

    ull i = 0;
    while (res[i] == 0)
        i++;

    while (i < res.size())
    {
        ans += std::to_string(res[i++]);
    }

    if (isNegative)
    {
        ans = '-' + ans;
    }

    if (total_p10 > 0)
    {
        ans.insert(ans.length() - total_p10, 1, '.');
        i = ans.length() - 1;
        bool isExtraZeroesAtEnd = true;
        while (i >= 0 && ans[i] != '.' && ans[i] == '0')
        {
            i--;
        }

        if (i != ans.length() - 1)
        {
            ans = ans.substr(0, i + 1);
        }
    }

    if (ans.back() == '.')
        ans.pop_back();

    return ans;
}

std::string ArithmeticExpressionWidget::divide(std::string &a, std::string &b)
{
    bool isNegative = false;

    if (a[0] == '-')
    {
        a.erase(0, 1);
        isNegative = !isNegative;
    }

    if (b[0] == '-')
    {
        b.erase(0, 1);
        isNegative = !isNegative;
    }
    removeTrailingZeroes(a);
    removeTrailingZeroes(b);
    if (a == "0" && b == "0")
        return "";
    if (a == "0")
        return "0";
    if (b == "0")
        return "";
    if (b == "1")
        return a;

    ll dec_pos_a = findDecimalIndexAndRemove(a);
    ll dec_pos_b = findDecimalIndexAndRemove(b);

    ull p10_a = dec_pos_a == -1 ? 0 : a.length() - dec_pos_a;
    ull p10_b = dec_pos_b == -1 ? 0 : b.length() - dec_pos_b;

    ull n = 0;
    std::string ans = "";
    int c = 0;
    while (a != "0" && c <= 1000)
    {
        n++;


        if (c != 0)
            c++;

        // cout << "A = " << a << endl;
        std::string div = subtract(a, b,true);

        // cout << "div = " << div << endl;
        if (div == "")
        {
            n--;
            ans += std::to_string(n);
            n = 0;
            if (c == 0)
                ans.push_back('.');
            c++;
            a.push_back('0');
        }
        else
        {
            a = div;
        }
    }

    if (n > 0)
        ans += std::to_string(n);

    ull dec_pos_ans = ans.find('.');
    if (dec_pos_ans != std::string::npos)
    {
        if (dec_pos_a != -1 && dec_pos_b == -1)
        {
            while (dec_pos_ans > 0 && p10_a)
            {
                std::swap(ans[dec_pos_ans], ans[dec_pos_ans - 1]);
                dec_pos_ans--;
                p10_a--;
            }
        }
        else if (dec_pos_b != -1 && dec_pos_a == -1)
        {
            while (dec_pos_ans < ans.length() - 1 && p10_b)
            {
                std::swap(ans[dec_pos_ans], ans[dec_pos_ans + 1]);
                dec_pos_ans++;
                p10_b--;
            }
        }
        else if (dec_pos_a != -1 && dec_pos_b != -1)
        {
            ans.erase(dec_pos_ans, 1);

            ull i = 0;
            while (i < ans.length() - 1 && ans[i] == '0')
            {
                i++;
            }
            // cout << "i = " << i << endl;
            ans = ans.substr(i);
            // cout << "ans = " << ans << endl;
            // return "";

            if (dec_pos_a == dec_pos_b)
            {
                ans.insert(1, 1, '.');
            }
            else if (dec_pos_a > dec_pos_b)
            {
                // cout << "decA = " << dec_pos_a << endl;
                // cout << "decB = " << dec_pos_b << endl;
                // return "";
                ull diff = dec_pos_a - dec_pos_b + 1;
                ans.insert(diff, 1, '.');
            }
            else
            {
                ans.insert(0, 1, '0');
                ans.insert(1, 1, '.');
            }
        }
    }

    ull i = 0;

    while (i < ans.length() - 1 && ans[i] == '0' && (ans[i + 1] != '.'))
    {
        i++;
    }

    ans = ans.substr(i);
    if (ans.back() == '.')
        ans.pop_back();

    if (isNegative)
        ans = '-' + ans;

    return ans;
}

std::string ArithmeticExpressionWidget::power(std::string &x, std::string &n)
{
    removeTrailingZeroes(x);

    bool isNegativePower = n[0] == '-';
    if (isNegativePower)
    {
        n = n.substr(1);
    }

    ull power_val = 0;
    for (ull i = 0; i < n.length(); i++)
    {
        int num = n[i] - '0';
        power_val = power_val * 10 + num;
    }

    if (power_val == 0)
    {
        return "1";
    }
    if (power_val == 1 && !isNegativePower)
    {
        return x;
    }

    std::string ans = "";
    std::string factor = (isNegativePower) ? "1" : x;
    power_val = (isNegativePower) ? power_val : power_val - 1;

    while (power_val)
    {

        factor = multiply(x, factor);

        power_val--;
    }
    if (isNegativePower)
    {
        std::string a = "1";
        factor = divide(a, factor);
    }
    return factor;
}

void ArithmeticExpressionWidget::removeTrailingZeroes(std::string &s)
{
    ull i = 0;

    while (i < s.length() && s.length() > 1 && s[i] == '0')
    {
        s.erase(i, 1);
    }
}

long long ArithmeticExpressionWidget::findDecimalIndexAndRemove(std::string &s)
{
    for (ull i = 0; i < s.length(); i++)
    {
        if (s[i] == '.')
        {
            s.erase(i, 1);
            return i;
        }
    }
    return -1;
}

std::string ArithmeticExpressionWidget::evaluatePostfix(std::string &postfix)
{
    std::stack<std::string> st;

    for(ull i=0 ; i<postfix.length() ; i++){
        if(postfix[i] == ' ') continue;

        else if(i < postfix.length()-1 && postfix[i] == '-' && postfix[i + 1] != ' '){
            std::string operand = "-";
            i++;

            while(i < postfix.length() && postfix[i]!=' '){
                operand.push_back(postfix[i++]);
            }

            st.push(operand);
        }

        else if(postfix[i] == '+' || postfix[i] == '-' || postfix[i] =='*' || postfix[i] =='/' ||postfix[i] == '^'){

            std::string op2 = st.top();
            st.pop();
            std::string op1 = st.top();
            st.pop();

            std::string ans = "";
            if(postfix[i] == '+'){
                ans = this->plus(op1,op2);
            }
            else if(postfix[i] == '-'){
                ans = this->subtract(op1,op2);
            }
            else if(postfix[i] == '/'){
                ans = this->divide(op1,op2);
            }
            else if(postfix[i] == '*'){
                ans = this->multiply(op1,op2);
            }
            else if(postfix[i] == '^'){
                ans = this->power(op1,op2);
            }

            if(ans.length() > 0){
                st.push(ans);
            }
            else{
                std::cout<<"ERROR: ans is empty."<<std::endl;
            }
        }

        else {
            std::string operand = "";

            while(i<postfix.length() && postfix[i]!=' '){
                operand.push_back(postfix[i++]);
            }

            st.push(operand);
        }
    }

    if(st.empty()){
        std::cout<<"ERROR: stack is empty."<<std::endl;
        return "";
    }

    return st.top();
}
