class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        vector<int> result;
        
        // 각 행의 최소값을 찾기
        vector<int> rowMins(matrix.size(), INT_MAX);
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] < rowMins[i]) {
                    rowMins[i] = matrix[i][j];
                }
            }
        }
        
        // 각 열의 최대값을 찾기
        vector<int> colMaxs(matrix[0].size(), INT_MIN);
        for (int j = 0; j < matrix[0].size(); ++j) {
            for (int i = 0; i < matrix.size(); ++i) {
                if (matrix[i][j] > colMaxs[j]) {
                    colMaxs[j] = matrix[i][j];
                }
            }
        }
        
        // 행의 최소값이면서 열의 최대값인 수 찾기
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == rowMins[i] && matrix[i][j] == colMaxs[j]) {
                    result.push_back(matrix[i][j]);
                }
            }
        }
        
        return result;
    }
};
