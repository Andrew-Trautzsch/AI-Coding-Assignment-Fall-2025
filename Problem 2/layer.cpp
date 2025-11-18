#include "ann.hpp"

const double threshold = 0.0;
const double lr = .03;

std::vector<double> Layer::computeOutput(const std::vector<double>& input)
{
    output_.resize(weights_.size()); saved_.resize(weights_.size());

    for(int i=0; i<weights_.size(); i++)
    {
        double sum = bias_[i];
        for(int j=0; j<weights_[i].size(); j++)
        {
            sum += weights_[i][j] * input[j];
        }

        saved_[i] = sum;              // store pre-activation value

        // Activation: threshold + sigmoid
        if (sum > threshold)
            output_[i] = sigmoid(sum);
        else
            output_[i] = 0.0;

    }

    return output_;
}

void Layer::updateWeights(const std::vector<double>& input)
{
    for(int i=0; i<weights_.size(); i++)
    {
        for(int j=0; j<weights_[i].size(); j++)
        {
            weights_[i][j] -= input[i] * delta_[i] * lr;
        }

        bias_[i] -= delta_[i] * lr;
    }
}
