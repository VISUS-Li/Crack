import param_gen
# "[{},{"actId":"60ccc3e1c9e77c000130ac38","token":"60ccc3e1c9e77c000130ac38"}]"
actid = "60ccc3e1c9e77c000130ac38"
a = param_gen.gen_hash(actid)
print(a)