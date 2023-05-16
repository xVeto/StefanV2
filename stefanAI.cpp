#include <bits/stdc++.h>
using namespace std;

vector <int> numNodesPerLayer = {2, 3, 2};
int numLayers = numNodesPerLayer.size(), numInputs = numNodesPerLayer[0], numOutputs = numNodesPerLayer[numNodesPerLayer.size()-1];

class hiddenLayers
{ public:
    int id;
    int numNodes, numNodesOut, numNodesIn;
    double bias[10010];
    double weights[1010][1010];
    
    void setNodes()
    {
        numNodes = numNodesPerLayer[id];

        if (id < numLayers-1) numNodesOut = numNodesPerLayer[id+1];
        else numNodesOut = numNodes;

        if (id > 0) numNodesIn = numNodesPerLayer[id-1];
        else numNodesIn = numNodes;
    }

    double Exp(double x)
    {
        return pow(2.718, x);
    }

    double activationFunc(double input)
    {
        return 1 / (1 + Exp(-input));
    }

    vector <double> calculate(double *&inputs)
    {
        double outputs[numNodesOut];
        vector <double> out;
        for (int i=0;i<numNodes;i++)
        {
            for (int j=0;j<numNodesOut;j++)
            {
                outputs[i] += (inputs[i] * weights[i][j] + bias[i]);
            }
        }
        for (int i=0;i<numNodes;i++) outputs[i] = activationFunc(outputs[i]);
        for (int i=numNodes-1;i>=0;i--) out.push_back(outputs[i]);
        return out;
    }
};

int main()
{
    srand(time(NULL));
    class hiddenLayers Layers[numLayers];
    
    string x;
    cin >> x;
    if (x == "calculate")
    {
        int n;

        ifstream file("weights.txt");
        file >> n;

        double w[1010][1010];
        int numN[n+3];

        for (int i=0;i<n;i++)
        {
            file >> numN[i];
        }

        for (int i=0;i<n-1;i++)
        {
            int a;
            for (int k=0;k<numN[i];k++)
            {
                for (int j=0;j<numN[i+1];j++)
                {
                    cin >> a;
                    w[k][j] = a;
                }
            }

            for (int k=0;k<numN[i];k++)
            {
                for (int j=0;j<numN[i+1];j++)
                {
                    Layers[i].weights[k][j] = w[k][j];
                }
            }
        }
    }
    
    double *tab = new double[numInputs+10];
    for (int i=0;i<numLayers;i++) Layers[i].setNodes();
    for (int i=0;i<numInputs;i++) cin >> tab[i];
    for (int i=0;i<numLayers-1;i++) Layers[i].id = i;
    for (int i=0;i<numLayers;i++) Layers[i].numNodes = numNodesPerLayer[i];

    //start neurons
    vector <double> layerOutput = Layers[0].calculate(tab);
    for (int i=0;i<numLayers;i++)
    {
        delete[] tab;
        tab = new double[numInputs+10];
        for (int i=0;i<layerOutput.size();i++)
        {
            tab[i] = layerOutput[i];
        }
        vector <double> layerOutput = Layers[i].calculate(tab);
    }

    pair <double,char> result={(int)-1e9,' '};
    int ktory=0;
    for (auto i:layerOutput) 
    {
        ktory++;

        result.first = i;
        if (result.first < i) 
        {
            switch (ktory)
            {
            case 1:
                result.second = 'w';
                break;

            case 2:
                result.second = 's';
                break;

            case 3:
                result.second = 'a';
                break;

            case 4:
                result.second = 'd';
                break;

            default:
                break;
            }
        }
    }

    cout << result.second;  

    return 0;
}