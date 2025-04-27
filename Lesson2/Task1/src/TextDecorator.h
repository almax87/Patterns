#include <string>
#include <iostream>
#include <iterator>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const  {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
    public:
        explicit Paragraph(Text* text) : DecoratedText(text) {}
        void render(const std::string& data) const {
            std::cout << "<p>";
            text_->render(data);
            std::cout << "</p>";
        }
    };

class Reversed : public DecoratedText{
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override{
        
        for (auto i = data.rbegin(); i <= data.rend(); i++)
        {
            std::cout << *i;
        }
    }
};

class Link : public DecoratedText {
    public:
        explicit Link(Text* text) : DecoratedText(text) {}
        void render(const std::string& url, const std::string& data) const {
            std::cout << "<a href=" + url + ">" ;
            text_->render(data);
            std::cout << "</a>";
        }
    };



