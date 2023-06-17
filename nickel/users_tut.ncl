let { UserSchema, .. } = import "users-schema.ncl" in
{
  users | Array UserSchema = [
    {
      name = "Alice",
      is-admin = true,
      extra-groups = ["support"],
      ssh-keys = [
        "AAAAAe4QAAAAAB5OLAo1...... alice@nixos",
        "AAAAA26vx+AqGIPZd/NT...... alice@android",
      ],
    },
    {
      name = "Bob",
      extra-groups = ["pentester"],
    },
    {
      name = "Mallory",
    },
    {
      name = "Grace",
      is-admin = true,
      extra-groups = ["administrative"],
    },
  ]
}
