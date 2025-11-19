#include "ann.hpp"

static const double threshold = 0.0;
static const double lr = 0.03;

std::vector<double> Layer::computeOutput(const std::vector<double>& input)
{
    int n = weights_.size();
    output_.resize(n);
    saved_.resize(n);

    for (int i = 0; i < n; i++)
    {
        double sum = bias_[i];
        for (int j = 0; j < weights_[i].size(); j++)
            sum += weights_[i][j] * input[j];

        saved_[i] = sum;

        if (sum > threshold)
            output_[i] = sigmoid(sum);
        else
            output_[i] = 0.0;
    }
    return output_;
}

void Layer::updateWeights(const std::vector<double>& input)
{
    for (int i = 0; i < weights_.size(); i++)
    {
        for (int j = 0; j < weights_[i].size(); j++)
        {
            double deltaW = lr * delta_[i] * input[j];
            weights_[i][j] -= deltaW;
        }
        bias_[i] -= lr * delta_[i];
    }
}

void Layer::printLayerInfo(const std::vector<double>& input, std::ostream& out) const
{
    out << "  Input:\n    ";
    for (double v : input) out << v << " ";
    out << "\n";

    out << "  Weights:\n";
    for (int i = 0; i < weights_.size(); i++)
    {
        out << "    Neuron " << i << ": ";
        for (double w : weights_[i]) out << w << " ";
        out << "\n";
    }

    out << "  Bias:\n    ";
    for (double b : bias_) out << b << " ";
    out << "\n";

    out << "  Output:\n    ";
    for (double v : output_) out << v << " ";
    out << "\n";
}

void Layer::printBackpropInfo(std::ostream& out) const
{
    out << "  Delta:\n    ";
    for (double d : delta_) out << d << " ";
    out << "\n";
}
