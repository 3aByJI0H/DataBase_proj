#pragma once

#include "date.h"

#include <string>
#include <memory>


class Node {
    public:
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
    public:
    bool Evaluate(const Date& date, const std::string& event) const override;
};

enum class Comparison {
    Less, 
    LessOrEqual, 
    Greater, 
    GreaterOrEqual, 
    Equal, 
    NotEqual
};

class DateComparisonNode : public Node {
    public:
    DateComparisonNode(const Comparison cmp, const Date& date);
    bool Evaluate(const Date& date, const std::string& event) const override;

    private:
    Date _condition_date;
    Comparison _cmp;
};

class EventComparisonNode : public Node {
    public:
    EventComparisonNode(const Comparison cmp, const std::string& value);
    bool Evaluate(const Date& date, const std::string& event) const override;

    private:
    std::string _condition_value;
    Comparison _cmp;
};

enum class LogicalOperation {
    Or,
    And
};

class LogicalOperationNode : public Node {
    public:
    LogicalOperationNode(const LogicalOperation logical_operation, 
        const std::shared_ptr<Node> left, const std::shared_ptr<Node> right
    );
    bool Evaluate(const Date& date, const std::string& event) const override;

    private:
    LogicalOperation _logical_operation;
    std::shared_ptr<Node> _left, _right;
};
