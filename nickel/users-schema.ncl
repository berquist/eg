{
  UserSchema =
  {
    name
      | String,
    is-admin
      | Bool
      | default
      = false,
    ssh-keys
      | Array String
      | optional,
    extra-groups
      | Array String
      | optional,
  }
}
