create table a (v vector(3) nullable);

insert into a values ('[1]');
insert into a values ('[1, 2]');
insert into a values ('[1, 2, 3]');
insert into a values ('[1, 2, 3, 4]');
insert into a values (null);

select * from a;