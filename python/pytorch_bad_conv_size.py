import torch

layer = torch.nn.Conv1d(16, 100, kernel_size=(5,), stride=(1,))
input_ok = torch.randn(294, 16, 7)
input_bad = torch.randn(470, 16, 4)
output_ok = layer(input_ok)
output_bad = layer(input_bad)
print(output_ok.size())
print(output_bad.size())
