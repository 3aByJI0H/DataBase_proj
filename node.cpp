#include "node.h"

#include <stdexcept>


bool EmptyNode::Evaluate(const Date& date, const std::string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison cmp, const Date& date) 
    : _condition_date(date), _cmp(cmp) {}
bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const {
    switch (_cmp) {
        case Comparison::Less:
        return date < _condition_date;

        case Comparison::LessOrEqual:
        return date <= _condition_date;

        case Comparison::Greater:
        return date > _condition_date;

        case Comparison::GreaterOrEqual:
        return date >= _condition_date;

        case Comparison::Equal:
        return date == _condition_date;

        case Comparison::NotEqual:
        return date != _condition_date;

        default:
        throw std::invalid_argument("Unknown comparison operation");
    }
    return true;
}

EventComparisonNode::EventComparisonNode(const Comparison cmp, const std::string& value)
    : _condition_value(value), _cmp(cmp) {} 
bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {
     switch (_cmp) {
        case Comparison::Less:
        return event < _condition_value;

        case Comparison::LessOrEqual:
        return event <= _condition_value;

        case Comparison::Greater:
        return event > _condition_value;

        case Comparison::GreaterOrEqual:
        return event >= _condition_value;

        case Comparison::Equal:
        return event == _condition_value;

        case Comparison::NotEqual:
        return event != _condition_value;

        default:
        throw std::invalid_argument("Unknown comparison operation");
    }
    return true;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation logical_operation, 
    const std::shared_ptr<Node> left, const std::shared_ptr<Node> right
) : _logical_operation(logical_operation), _left(left), _right(right) {}
bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const {
    switch (_logical_operation) {
        case LogicalOperation::Or:
        return _left->Evaluate(date, event) or _right->Evaluate(date, event);

        case LogicalOperation::And:
        return _left->Evaluate(date, event) and _right->Evaluate(date, event); 

        default:
        throw std::invalid_argument("Unknown logical operation");
    }
    return true;
}
